/*
 * Lab5_Model.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Lab5_Model".
 *
 * Model version              : 7.4
 * Simulink Coder version : 9.7 (R2022a) 13-Nov-2021
 * C source code generated on : Tue Nov 15 11:43:05 2022
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Lab5_Model.h"
#include "rtwtypes.h"
#include "Lab5_Model_private.h"
#include "rt_nonfinite.h"
#include "Lab5_Model_dt.h"

/* Block signals (default storage) */
B_Lab5_Model_T Lab5_Model_B;

/* Continuous states */
X_Lab5_Model_T Lab5_Model_X;

/* Block states (default storage) */
DW_Lab5_Model_T Lab5_Model_DW;

/* Real-time model */
static RT_MODEL_Lab5_Model_T Lab5_Model_M_;
RT_MODEL_Lab5_Model_T *const Lab5_Model_M = &Lab5_Model_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 5;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Lab5_Model_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  Lab5_Model_output();
  Lab5_Model_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  Lab5_Model_output();
  Lab5_Model_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void Lab5_Model_output(void)
{
  real_T rtb_DataTypeConversion;
  real_T rtb_Sum1;
  real_T rtb_Tank2RawFilter;
  real_T u0;
  real_T *lastU;
  int32_T rowIdx;
  boolean_T rtb_AND2;
  boolean_T rtb_NOR;
  if (rtmIsMajorTimeStep(Lab5_Model_M)) {
    /* set solver stop time */
    if (!(Lab5_Model_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&Lab5_Model_M->solverInfo,
                            ((Lab5_Model_M->Timing.clockTickH0 + 1) *
        Lab5_Model_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&Lab5_Model_M->solverInfo,
                            ((Lab5_Model_M->Timing.clockTick0 + 1) *
        Lab5_Model_M->Timing.stepSize0 + Lab5_Model_M->Timing.clockTickH0 *
        Lab5_Model_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Lab5_Model_M)) {
    Lab5_Model_M->Timing.t[0] = rtsiGetT(&Lab5_Model_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(Lab5_Model_M)) {
  }

  /* TransferFcn: '<S2>/Tank 2 Output Filter' */
  Lab5_Model_B.Tank2OutputFilter = 0.0;
  Lab5_Model_B.Tank2OutputFilter += Lab5_Model_P.Tank2OutputFilter_C *
    Lab5_Model_X.Tank2OutputFilter_CSTATE;

  /* Step: '<Root>/Step' */
  if (Lab5_Model_M->Timing.t[0] < Lab5_Model_P.Step_Time) {
    /* Step: '<Root>/Step' */
    Lab5_Model_B.Step = Lab5_Model_P.Step_Y0;
  } else {
    /* Step: '<Root>/Step' */
    Lab5_Model_B.Step = Lab5_Model_P.Step_YFinal;
  }

  /* End of Step: '<Root>/Step' */

  /* Sum: '<Root>/Sum1' */
  rtb_Sum1 = Lab5_Model_B.Step - Lab5_Model_B.Tank2OutputFilter;

  /* Sum: '<Root>/Sum' incorporates:
   *  Gain: '<Root>/Gain2'
   *  Integrator: '<Root>/Integrator'
   *  TransferFcn: '<Root>/Transfer Fcn'
   */
  u0 = (Lab5_Model_P.TransferFcn_C * Lab5_Model_X.TransferFcn_CSTATE +
        Lab5_Model_P.Kp * rtb_Sum1) + Lab5_Model_X.Integrator_CSTATE;

  /* TransferFcn: '<S2>/Tank 1 Raw Filter' */
  rtb_DataTypeConversion = Lab5_Model_P.Tank1RawFilter_C *
    Lab5_Model_X.Tank1RawFilter_CSTATE;

  /* TransferFcn: '<S2>/Tank 2 Raw Filter' */
  rtb_Tank2RawFilter = Lab5_Model_P.Tank2RawFilter_C *
    Lab5_Model_X.Tank2RawFilter_CSTATE;

  /* Logic: '<S2>/OR1' incorporates:
   *  Constant: '<S2>/Tank 1 Restart Level'
   *  Constant: '<S2>/Tank 2 Restart Level'
   *  RelationalOperator: '<S2>/Less Than2'
   *  RelationalOperator: '<S2>/Less Than3'
   */
  rtb_AND2 = ((rtb_DataTypeConversion >= Lab5_Model_P.Tank1RestartLevel_Value) ||
              (rtb_Tank2RawFilter >= Lab5_Model_P.Tank2RestartLevel_Value));

  /* Logic: '<S2>/AND' incorporates:
   *  Constant: '<S2>/Tank 1 Stop Limit'
   *  Constant: '<S2>/Tank 2 Stop Limit'
   *  Logic: '<S2>/OR'
   *  RelationalOperator: '<S2>/Less Than'
   *  RelationalOperator: '<S2>/Less Than1'
   */
  rtb_NOR = (((rtb_DataTypeConversion >= Lab5_Model_P.Tank1StopLimit_Value) ||
              (rtb_Tank2RawFilter >= Lab5_Model_P.Tank2StopLimit_Value)) &&
             rtb_AND2);

  /* Logic: '<S2>/NOT' */
  rtb_AND2 = !rtb_AND2;
  if (rtmIsMajorTimeStep(Lab5_Model_M)) {
    /* Memory: '<S3>/Memory' */
    Lab5_Model_B.Memory = Lab5_Model_DW.Memory_PreviousInput;
  }

  /* CombinatorialLogic: '<S3>/Logic' */
  rowIdx = (int32_T)(((((uint32_T)rtb_NOR << 1) + rtb_AND2) << 1) +
                     Lab5_Model_B.Memory);
  Lab5_Model_B.Logic[0U] = Lab5_Model_P.Logic_table[(uint32_T)rowIdx];
  Lab5_Model_B.Logic[1U] = Lab5_Model_P.Logic_table[rowIdx + 8U];
  if (rtmIsMajorTimeStep(Lab5_Model_M)) {
    /* S-Function (hil_read_analog_block): '<Root>/HIL Read Analog' */

    /* S-Function Block: Lab5_Model/HIL Read Analog (hil_read_analog_block) */
    {
      t_error result = hil_read_analog(Lab5_Model_DW.HILInitialize_Card,
        Lab5_Model_P.HILReadAnalog_channels, 2,
        &Lab5_Model_DW.HILReadAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab5_Model_M, _rt_error_message);
      }

      Lab5_Model_B.HILReadAnalog_o1 = Lab5_Model_DW.HILReadAnalog_Buffer[0];
      Lab5_Model_B.HILReadAnalog_o2 = Lab5_Model_DW.HILReadAnalog_Buffer[1];
    }

    /* MATLAB Function: '<Root>/Tank 2 Calibration' */
    Lab5_Model_B.y = 6.08 * Lab5_Model_B.HILReadAnalog_o2 + 0.71;

    /* CombinatorialLogic: '<S4>/Logic' incorporates:
     *  Memory: '<S4>/Memory'
     *  RelationalOperator: '<S2>/Equal1'
     */
    rowIdx = (int32_T)(((((uint32_T)(Lab5_Model_B.HILReadAnalog_o2 !=
      Lab5_Model_B.y) << 1) + false) << 1) +
                       Lab5_Model_DW.Memory_PreviousInput_k);
    Lab5_Model_B.Logic_i[0U] = Lab5_Model_P.Logic_table_e[(uint32_T)rowIdx];
    Lab5_Model_B.Logic_i[1U] = Lab5_Model_P.Logic_table_e[rowIdx + 8U];
  }

  /* Saturate: '<Root>/Saturation' */
  if (u0 > Lab5_Model_P.Saturation_UpperSat) {
    u0 = Lab5_Model_P.Saturation_UpperSat;
  } else if (u0 < Lab5_Model_P.Saturation_LowerSat) {
    u0 = Lab5_Model_P.Saturation_LowerSat;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* Product: '<S2>/Multiply' incorporates:
   *  Constant: '<S2>/Combined Voltage Limit'
   *  DataTypeConversion: '<S2>/Data Type Conversion'
   *  Gain: '<Root>/Gain'
   *  Logic: '<S2>/AND1'
   *  Logic: '<S2>/AND2'
   *  Logic: '<S2>/NOR'
   *  RelationalOperator: '<S2>/Less Than4'
   *  Sum: '<S2>/Sum'
   */
  Lab5_Model_B.Multiply = (real_T)(((!Lab5_Model_B.Logic[0]) ||
    (!Lab5_Model_B.Logic_i[0])) && ((!(rtb_DataTypeConversion +
    rtb_Tank2RawFilter >= Lab5_Model_P.CombinedVoltageLimit_Value)) ||
    (!Lab5_Model_B.Logic_i[1]))) * (Lab5_Model_P.Gain_Gain * u0);
  if (rtmIsMajorTimeStep(Lab5_Model_M)) {
    /* S-Function (hil_write_analog_block): '<Root>/HIL Write Analog' */

    /* S-Function Block: Lab5_Model/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      result = hil_write_analog(Lab5_Model_DW.HILInitialize_Card,
        &Lab5_Model_P.HILWriteAnalog_channels, 1, &Lab5_Model_B.Multiply);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab5_Model_M, _rt_error_message);
      }
    }
  }

  /* Gain: '<Root>/Gain1' */
  Lab5_Model_B.Gain1 = Lab5_Model_P.Kd * rtb_Sum1;

  /* Derivative: '<Root>/Derivative' */
  rtb_DataTypeConversion = Lab5_Model_M->Timing.t[0];
  if ((Lab5_Model_DW.TimeStampA >= rtb_DataTypeConversion) &&
      (Lab5_Model_DW.TimeStampB >= rtb_DataTypeConversion)) {
    /* Derivative: '<Root>/Derivative' */
    Lab5_Model_B.Derivative = 0.0;
  } else {
    rtb_Tank2RawFilter = Lab5_Model_DW.TimeStampA;
    lastU = &Lab5_Model_DW.LastUAtTimeA;
    if (Lab5_Model_DW.TimeStampA < Lab5_Model_DW.TimeStampB) {
      if (Lab5_Model_DW.TimeStampB < rtb_DataTypeConversion) {
        rtb_Tank2RawFilter = Lab5_Model_DW.TimeStampB;
        lastU = &Lab5_Model_DW.LastUAtTimeB;
      }
    } else if (Lab5_Model_DW.TimeStampA >= rtb_DataTypeConversion) {
      rtb_Tank2RawFilter = Lab5_Model_DW.TimeStampB;
      lastU = &Lab5_Model_DW.LastUAtTimeB;
    }

    /* Derivative: '<Root>/Derivative' */
    Lab5_Model_B.Derivative = (Lab5_Model_B.Gain1 - *lastU) /
      (rtb_DataTypeConversion - rtb_Tank2RawFilter);
  }

  /* End of Derivative: '<Root>/Derivative' */

  /* Gain: '<Root>/Gain3' */
  Lab5_Model_B.Gain3 = Lab5_Model_P.Ki * rtb_Sum1;
}

/* Model update function */
void Lab5_Model_update(void)
{
  real_T *lastU;
  if (rtmIsMajorTimeStep(Lab5_Model_M)) {
    /* Update for Memory: '<S3>/Memory' */
    Lab5_Model_DW.Memory_PreviousInput = Lab5_Model_B.Logic[0];

    /* Update for Memory: '<S4>/Memory' */
    Lab5_Model_DW.Memory_PreviousInput_k = Lab5_Model_B.Logic_i[0];
  }

  /* Update for Derivative: '<Root>/Derivative' */
  if (Lab5_Model_DW.TimeStampA == (rtInf)) {
    Lab5_Model_DW.TimeStampA = Lab5_Model_M->Timing.t[0];
    lastU = &Lab5_Model_DW.LastUAtTimeA;
  } else if (Lab5_Model_DW.TimeStampB == (rtInf)) {
    Lab5_Model_DW.TimeStampB = Lab5_Model_M->Timing.t[0];
    lastU = &Lab5_Model_DW.LastUAtTimeB;
  } else if (Lab5_Model_DW.TimeStampA < Lab5_Model_DW.TimeStampB) {
    Lab5_Model_DW.TimeStampA = Lab5_Model_M->Timing.t[0];
    lastU = &Lab5_Model_DW.LastUAtTimeA;
  } else {
    Lab5_Model_DW.TimeStampB = Lab5_Model_M->Timing.t[0];
    lastU = &Lab5_Model_DW.LastUAtTimeB;
  }

  *lastU = Lab5_Model_B.Gain1;

  /* End of Update for Derivative: '<Root>/Derivative' */
  if (rtmIsMajorTimeStep(Lab5_Model_M)) {
    rt_ertODEUpdateContinuousStates(&Lab5_Model_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Lab5_Model_M->Timing.clockTick0)) {
    ++Lab5_Model_M->Timing.clockTickH0;
  }

  Lab5_Model_M->Timing.t[0] = rtsiGetSolverStopTime(&Lab5_Model_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++Lab5_Model_M->Timing.clockTick1)) {
      ++Lab5_Model_M->Timing.clockTickH1;
    }

    Lab5_Model_M->Timing.t[1] = Lab5_Model_M->Timing.clockTick1 *
      Lab5_Model_M->Timing.stepSize1 + Lab5_Model_M->Timing.clockTickH1 *
      Lab5_Model_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void Lab5_Model_derivatives(void)
{
  XDot_Lab5_Model_T *_rtXdot;
  _rtXdot = ((XDot_Lab5_Model_T *) Lab5_Model_M->derivs);

  /* Derivatives for TransferFcn: '<S2>/Tank 2 Output Filter' */
  _rtXdot->Tank2OutputFilter_CSTATE = Lab5_Model_P.Tank2OutputFilter_A *
    Lab5_Model_X.Tank2OutputFilter_CSTATE;
  _rtXdot->Tank2OutputFilter_CSTATE += Lab5_Model_B.y;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = Lab5_Model_P.TransferFcn_A *
    Lab5_Model_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += Lab5_Model_B.Derivative;

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = Lab5_Model_B.Gain3;

  /* Derivatives for TransferFcn: '<S2>/Tank 1 Raw Filter' */
  _rtXdot->Tank1RawFilter_CSTATE = Lab5_Model_P.Tank1RawFilter_A *
    Lab5_Model_X.Tank1RawFilter_CSTATE;
  _rtXdot->Tank1RawFilter_CSTATE += Lab5_Model_B.HILReadAnalog_o1;

  /* Derivatives for TransferFcn: '<S2>/Tank 2 Raw Filter' */
  _rtXdot->Tank2RawFilter_CSTATE = Lab5_Model_P.Tank2RawFilter_A *
    Lab5_Model_X.Tank2RawFilter_CSTATE;
  _rtXdot->Tank2RawFilter_CSTATE += Lab5_Model_B.HILReadAnalog_o2;
}

/* Model initialize function */
void Lab5_Model_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Lab5_Model/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &Lab5_Model_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab5_Model_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(Lab5_Model_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab5_Model_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(Lab5_Model_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab5_Model_M, _rt_error_message);
      return;
    }

    if ((Lab5_Model_P.HILInitialize_AIPStart && !is_switching) ||
        (Lab5_Model_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &Lab5_Model_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (Lab5_Model_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &Lab5_Model_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = Lab5_Model_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(Lab5_Model_DW.HILInitialize_Card,
        Lab5_Model_P.HILInitialize_AIChannels, 8U,
        &Lab5_Model_DW.HILInitialize_AIMinimums[0],
        &Lab5_Model_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab5_Model_M, _rt_error_message);
        return;
      }
    }

    if ((Lab5_Model_P.HILInitialize_AOPStart && !is_switching) ||
        (Lab5_Model_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &Lab5_Model_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (Lab5_Model_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &Lab5_Model_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = Lab5_Model_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges(Lab5_Model_DW.HILInitialize_Card,
        Lab5_Model_P.HILInitialize_AOChannels, 8U,
        &Lab5_Model_DW.HILInitialize_AOMinimums[0],
        &Lab5_Model_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab5_Model_M, _rt_error_message);
        return;
      }
    }

    if ((Lab5_Model_P.HILInitialize_AOStart && !is_switching) ||
        (Lab5_Model_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Lab5_Model_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab5_Model_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(Lab5_Model_DW.HILInitialize_Card,
        Lab5_Model_P.HILInitialize_AOChannels, 8U,
        &Lab5_Model_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab5_Model_M, _rt_error_message);
        return;
      }
    }

    if (Lab5_Model_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Lab5_Model_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab5_Model_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (Lab5_Model_DW.HILInitialize_Card, Lab5_Model_P.HILInitialize_AOChannels,
         8U, &Lab5_Model_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab5_Model_M, _rt_error_message);
        return;
      }
    }

    if ((Lab5_Model_P.HILInitialize_EIPStart && !is_switching) ||
        (Lab5_Model_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &Lab5_Model_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = Lab5_Model_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(Lab5_Model_DW.HILInitialize_Card,
        Lab5_Model_P.HILInitialize_EIChannels, 8U, (t_encoder_quadrature_mode *)
        &Lab5_Model_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab5_Model_M, _rt_error_message);
        return;
      }
    }

    if ((Lab5_Model_P.HILInitialize_EIStart && !is_switching) ||
        (Lab5_Model_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &Lab5_Model_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = Lab5_Model_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(Lab5_Model_DW.HILInitialize_Card,
        Lab5_Model_P.HILInitialize_EIChannels, 8U,
        &Lab5_Model_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab5_Model_M, _rt_error_message);
        return;
      }
    }

    if ((Lab5_Model_P.HILInitialize_POPStart && !is_switching) ||
        (Lab5_Model_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &Lab5_Model_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = Lab5_Model_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(Lab5_Model_DW.HILInitialize_Card,
        Lab5_Model_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &Lab5_Model_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab5_Model_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          Lab5_Model_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues = &Lab5_Model_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            Lab5_Model_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              (p_HILInitialize_POChannels[i1]);
            Lab5_Model_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              Lab5_Model_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            Lab5_Model_DW.HILInitialize_POSortedChans[7U - num_frequency_modes] =
              (p_HILInitialize_POChannels[i1]);
            Lab5_Model_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes] =
              Lab5_Model_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(Lab5_Model_DW.HILInitialize_Card,
          &Lab5_Model_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &Lab5_Model_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab5_Model_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(Lab5_Model_DW.HILInitialize_Card,
          &Lab5_Model_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &Lab5_Model_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab5_Model_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &Lab5_Model_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = Lab5_Model_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &Lab5_Model_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = Lab5_Model_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &Lab5_Model_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = Lab5_Model_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(Lab5_Model_DW.HILInitialize_Card,
        Lab5_Model_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &Lab5_Model_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &Lab5_Model_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &Lab5_Model_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab5_Model_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &Lab5_Model_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = Lab5_Model_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &Lab5_Model_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab5_Model_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(Lab5_Model_DW.HILInitialize_Card,
        Lab5_Model_P.HILInitialize_POChannels, 8U,
        &Lab5_Model_DW.HILInitialize_POSortedFreqs[0],
        &Lab5_Model_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab5_Model_M, _rt_error_message);
        return;
      }
    }

    if ((Lab5_Model_P.HILInitialize_POStart && !is_switching) ||
        (Lab5_Model_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab5_Model_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab5_Model_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(Lab5_Model_DW.HILInitialize_Card,
        Lab5_Model_P.HILInitialize_POChannels, 8U,
        &Lab5_Model_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab5_Model_M, _rt_error_message);
        return;
      }
    }

    if (Lab5_Model_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab5_Model_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab5_Model_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (Lab5_Model_DW.HILInitialize_Card, Lab5_Model_P.HILInitialize_POChannels,
         8U, &Lab5_Model_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab5_Model_M, _rt_error_message);
        return;
      }
    }
  }

  /* InitializeConditions for TransferFcn: '<S2>/Tank 2 Output Filter' */
  Lab5_Model_X.Tank2OutputFilter_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  Lab5_Model_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  Lab5_Model_X.Integrator_CSTATE = Lab5_Model_P.Integrator_IC;

  /* InitializeConditions for TransferFcn: '<S2>/Tank 1 Raw Filter' */
  Lab5_Model_X.Tank1RawFilter_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Tank 2 Raw Filter' */
  Lab5_Model_X.Tank2RawFilter_CSTATE = 0.0;

  /* InitializeConditions for Memory: '<S3>/Memory' */
  Lab5_Model_DW.Memory_PreviousInput = Lab5_Model_P.SRFlipFlop_initial_condition;

  /* InitializeConditions for Memory: '<S4>/Memory' */
  Lab5_Model_DW.Memory_PreviousInput_k =
    Lab5_Model_P.SRFlipFlop1_initial_condition;

  /* InitializeConditions for Derivative: '<Root>/Derivative' */
  Lab5_Model_DW.TimeStampA = (rtInf);
  Lab5_Model_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void Lab5_Model_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Lab5_Model/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(Lab5_Model_DW.HILInitialize_Card);
    hil_monitor_stop_all(Lab5_Model_DW.HILInitialize_Card);
    is_switching = false;
    if ((Lab5_Model_P.HILInitialize_AOTerminate && !is_switching) ||
        (Lab5_Model_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Lab5_Model_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab5_Model_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((Lab5_Model_P.HILInitialize_POTerminate && !is_switching) ||
        (Lab5_Model_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab5_Model_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab5_Model_P.HILInitialize_POFinal;
        }
      }

      num_final_pwm_outputs = 8U;
    } else {
      num_final_pwm_outputs = 0;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(Lab5_Model_DW.HILInitialize_Card
                         , Lab5_Model_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , Lab5_Model_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &Lab5_Model_DW.HILInitialize_AOVoltages[0]
                         , &Lab5_Model_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(Lab5_Model_DW.HILInitialize_Card,
            Lab5_Model_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &Lab5_Model_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(Lab5_Model_DW.HILInitialize_Card,
            Lab5_Model_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &Lab5_Model_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab5_Model_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(Lab5_Model_DW.HILInitialize_Card);
    hil_monitor_delete_all(Lab5_Model_DW.HILInitialize_Card);
    hil_close(Lab5_Model_DW.HILInitialize_Card);
    Lab5_Model_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  Lab5_Model_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  Lab5_Model_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  Lab5_Model_initialize();
}

void MdlTerminate(void)
{
  Lab5_Model_terminate();
}

/* Registration function */
RT_MODEL_Lab5_Model_T *Lab5_Model(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Lab5_Model_M, 0,
                sizeof(RT_MODEL_Lab5_Model_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Lab5_Model_M->solverInfo,
                          &Lab5_Model_M->Timing.simTimeStep);
    rtsiSetTPtr(&Lab5_Model_M->solverInfo, &rtmGetTPtr(Lab5_Model_M));
    rtsiSetStepSizePtr(&Lab5_Model_M->solverInfo,
                       &Lab5_Model_M->Timing.stepSize0);
    rtsiSetdXPtr(&Lab5_Model_M->solverInfo, &Lab5_Model_M->derivs);
    rtsiSetContStatesPtr(&Lab5_Model_M->solverInfo, (real_T **)
                         &Lab5_Model_M->contStates);
    rtsiSetNumContStatesPtr(&Lab5_Model_M->solverInfo,
      &Lab5_Model_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&Lab5_Model_M->solverInfo,
      &Lab5_Model_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&Lab5_Model_M->solverInfo,
      &Lab5_Model_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&Lab5_Model_M->solverInfo,
      &Lab5_Model_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&Lab5_Model_M->solverInfo, (&rtmGetErrorStatus
      (Lab5_Model_M)));
    rtsiSetRTModelPtr(&Lab5_Model_M->solverInfo, Lab5_Model_M);
  }

  rtsiSetSimTimeStep(&Lab5_Model_M->solverInfo, MAJOR_TIME_STEP);
  Lab5_Model_M->intgData.y = Lab5_Model_M->odeY;
  Lab5_Model_M->intgData.f[0] = Lab5_Model_M->odeF[0];
  Lab5_Model_M->intgData.f[1] = Lab5_Model_M->odeF[1];
  Lab5_Model_M->intgData.f[2] = Lab5_Model_M->odeF[2];
  Lab5_Model_M->contStates = ((real_T *) &Lab5_Model_X);
  rtsiSetSolverData(&Lab5_Model_M->solverInfo, (void *)&Lab5_Model_M->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&Lab5_Model_M->solverInfo, false);
  rtsiSetSolverName(&Lab5_Model_M->solverInfo,"ode3");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Lab5_Model_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "Lab5_Model_M points to
       static memory which is guaranteed to be non-NULL" */
    Lab5_Model_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Lab5_Model_M->Timing.sampleTimes = (&Lab5_Model_M->Timing.sampleTimesArray[0]);
    Lab5_Model_M->Timing.offsetTimes = (&Lab5_Model_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Lab5_Model_M->Timing.sampleTimes[0] = (0.0);
    Lab5_Model_M->Timing.sampleTimes[1] = (0.001);

    /* task offsets */
    Lab5_Model_M->Timing.offsetTimes[0] = (0.0);
    Lab5_Model_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(Lab5_Model_M, &Lab5_Model_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Lab5_Model_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    Lab5_Model_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Lab5_Model_M, 300.0);
  Lab5_Model_M->Timing.stepSize0 = 0.001;
  Lab5_Model_M->Timing.stepSize1 = 0.001;

  /* External mode info */
  Lab5_Model_M->Sizes.checksums[0] = (2568875386U);
  Lab5_Model_M->Sizes.checksums[1] = (1710945936U);
  Lab5_Model_M->Sizes.checksums[2] = (2572294066U);
  Lab5_Model_M->Sizes.checksums[3] = (3569378334U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    Lab5_Model_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Lab5_Model_M->extModeInfo,
      &Lab5_Model_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Lab5_Model_M->extModeInfo, Lab5_Model_M->Sizes.checksums);
    rteiSetTPtr(Lab5_Model_M->extModeInfo, rtmGetTPtr(Lab5_Model_M));
  }

  Lab5_Model_M->solverInfoPtr = (&Lab5_Model_M->solverInfo);
  Lab5_Model_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&Lab5_Model_M->solverInfo, 0.001);
  rtsiSetSolverMode(&Lab5_Model_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  Lab5_Model_M->blockIO = ((void *) &Lab5_Model_B);
  (void) memset(((void *) &Lab5_Model_B), 0,
                sizeof(B_Lab5_Model_T));

  /* parameters */
  Lab5_Model_M->defaultParam = ((real_T *)&Lab5_Model_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &Lab5_Model_X;
    Lab5_Model_M->contStates = (x);
    (void) memset((void *)&Lab5_Model_X, 0,
                  sizeof(X_Lab5_Model_T));
  }

  /* states (dwork) */
  Lab5_Model_M->dwork = ((void *) &Lab5_Model_DW);
  (void) memset((void *)&Lab5_Model_DW, 0,
                sizeof(DW_Lab5_Model_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    Lab5_Model_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 19;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  Lab5_Model_M->Sizes.numContStates = (5);/* Number of continuous states */
  Lab5_Model_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  Lab5_Model_M->Sizes.numY = (0);      /* Number of model outputs */
  Lab5_Model_M->Sizes.numU = (0);      /* Number of model inputs */
  Lab5_Model_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  Lab5_Model_M->Sizes.numSampTimes = (2);/* Number of sample times */
  Lab5_Model_M->Sizes.numBlocks = (47);/* Number of blocks */
  Lab5_Model_M->Sizes.numBlockIO = (12);/* Number of block outputs */
  Lab5_Model_M->Sizes.numBlockPrms = (156);/* Sum of parameter "widths" */
  return Lab5_Model_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/

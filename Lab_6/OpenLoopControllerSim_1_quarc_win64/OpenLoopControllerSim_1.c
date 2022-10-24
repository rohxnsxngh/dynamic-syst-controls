/*
 * OpenLoopControllerSim_1.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "OpenLoopControllerSim_1".
 *
 * Model version              : 7.0
 * Simulink Coder version : 9.7 (R2022a) 13-Nov-2021
 * C source code generated on : Tue Oct 18 11:25:42 2022
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "OpenLoopControllerSim_1.h"
#include "OpenLoopControllerSim_1_private.h"
#include "rt_nonfinite.h"
#include "OpenLoopControllerSim_1_dt.h"

/* Block signals (default storage) */
B_OpenLoopControllerSim_1_T OpenLoopControllerSim_1_B;

/* Continuous states */
X_OpenLoopControllerSim_1_T OpenLoopControllerSim_1_X;

/* Block states (default storage) */
DW_OpenLoopControllerSim_1_T OpenLoopControllerSim_1_DW;

/* Real-time model */
static RT_MODEL_OpenLoopControllerSi_T OpenLoopControllerSim_1_M_;
RT_MODEL_OpenLoopControllerSi_T *const OpenLoopControllerSim_1_M =
  &OpenLoopControllerSim_1_M_;

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
  int_T nXc = 1;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  OpenLoopControllerSim_1_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  OpenLoopControllerSim_1_output();
  OpenLoopControllerSim_1_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  OpenLoopControllerSim_1_output();
  OpenLoopControllerSim_1_derivatives();

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
void OpenLoopControllerSim_1_output(void)
{
  if (rtmIsMajorTimeStep(OpenLoopControllerSim_1_M)) {
    /* set solver stop time */
    if (!(OpenLoopControllerSim_1_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&OpenLoopControllerSim_1_M->solverInfo,
                            ((OpenLoopControllerSim_1_M->Timing.clockTickH0 + 1)
        * OpenLoopControllerSim_1_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&OpenLoopControllerSim_1_M->solverInfo,
                            ((OpenLoopControllerSim_1_M->Timing.clockTick0 + 1) *
        OpenLoopControllerSim_1_M->Timing.stepSize0 +
        OpenLoopControllerSim_1_M->Timing.clockTickH0 *
        OpenLoopControllerSim_1_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(OpenLoopControllerSim_1_M)) {
    OpenLoopControllerSim_1_M->Timing.t[0] = rtsiGetT
      (&OpenLoopControllerSim_1_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(OpenLoopControllerSim_1_M)) {
  }

  /* TransferFcn: '<Root>/Transfer Fcn' */
  OpenLoopControllerSim_1_B.TransferFcn = 0.0;
  OpenLoopControllerSim_1_B.TransferFcn +=
    OpenLoopControllerSim_1_P.TransferFcn_C *
    OpenLoopControllerSim_1_X.TransferFcn_CSTATE;
  if (rtmIsMajorTimeStep(OpenLoopControllerSim_1_M)) {
    /* Gain: '<Root>/Gain' incorporates:
     *  Constant: '<Root>/Constant'
     */
    OpenLoopControllerSim_1_B.Gain = OpenLoopControllerSim_1_P.Gain_Gain *
      OpenLoopControllerSim_1_P.Constant_Value;
  }
}

/* Model update function */
void OpenLoopControllerSim_1_update(void)
{
  if (rtmIsMajorTimeStep(OpenLoopControllerSim_1_M)) {
    rt_ertODEUpdateContinuousStates(&OpenLoopControllerSim_1_M->solverInfo);
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
  if (!(++OpenLoopControllerSim_1_M->Timing.clockTick0)) {
    ++OpenLoopControllerSim_1_M->Timing.clockTickH0;
  }

  OpenLoopControllerSim_1_M->Timing.t[0] = rtsiGetSolverStopTime
    (&OpenLoopControllerSim_1_M->solverInfo);

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
    if (!(++OpenLoopControllerSim_1_M->Timing.clockTick1)) {
      ++OpenLoopControllerSim_1_M->Timing.clockTickH1;
    }

    OpenLoopControllerSim_1_M->Timing.t[1] =
      OpenLoopControllerSim_1_M->Timing.clockTick1 *
      OpenLoopControllerSim_1_M->Timing.stepSize1 +
      OpenLoopControllerSim_1_M->Timing.clockTickH1 *
      OpenLoopControllerSim_1_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void OpenLoopControllerSim_1_derivatives(void)
{
  XDot_OpenLoopControllerSim_1_T *_rtXdot;
  _rtXdot = ((XDot_OpenLoopControllerSim_1_T *)
             OpenLoopControllerSim_1_M->derivs);

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = OpenLoopControllerSim_1_P.TransferFcn_A *
    OpenLoopControllerSim_1_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += OpenLoopControllerSim_1_B.Gain;
}

/* Model initialize function */
void OpenLoopControllerSim_1_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: OpenLoopControllerSim_1/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0",
                      &OpenLoopControllerSim_1_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(OpenLoopControllerSim_1_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (OpenLoopControllerSim_1_DW.HILInitialize_Card,
       "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(OpenLoopControllerSim_1_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(OpenLoopControllerSim_1_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(OpenLoopControllerSim_1_M, _rt_error_message);
      return;
    }

    if ((OpenLoopControllerSim_1_P.HILInitialize_AIPStart && !is_switching) ||
        (OpenLoopControllerSim_1_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums =
          &OpenLoopControllerSim_1_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (OpenLoopControllerSim_1_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums =
          &OpenLoopControllerSim_1_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = OpenLoopControllerSim_1_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges
        (OpenLoopControllerSim_1_DW.HILInitialize_Card,
         OpenLoopControllerSim_1_P.HILInitialize_AIChannels, 8U,
         &OpenLoopControllerSim_1_DW.HILInitialize_AIMinimums[0],
         &OpenLoopControllerSim_1_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(OpenLoopControllerSim_1_M, _rt_error_message);
        return;
      }
    }

    if ((OpenLoopControllerSim_1_P.HILInitialize_AOPStart && !is_switching) ||
        (OpenLoopControllerSim_1_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums =
          &OpenLoopControllerSim_1_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (OpenLoopControllerSim_1_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums =
          &OpenLoopControllerSim_1_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = OpenLoopControllerSim_1_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges
        (OpenLoopControllerSim_1_DW.HILInitialize_Card,
         OpenLoopControllerSim_1_P.HILInitialize_AOChannels, 8U,
         &OpenLoopControllerSim_1_DW.HILInitialize_AOMinimums[0],
         &OpenLoopControllerSim_1_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(OpenLoopControllerSim_1_M, _rt_error_message);
        return;
      }
    }

    if ((OpenLoopControllerSim_1_P.HILInitialize_AOStart && !is_switching) ||
        (OpenLoopControllerSim_1_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &OpenLoopControllerSim_1_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = OpenLoopControllerSim_1_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(OpenLoopControllerSim_1_DW.HILInitialize_Card,
        OpenLoopControllerSim_1_P.HILInitialize_AOChannels, 8U,
        &OpenLoopControllerSim_1_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(OpenLoopControllerSim_1_M, _rt_error_message);
        return;
      }
    }

    if (OpenLoopControllerSim_1_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &OpenLoopControllerSim_1_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = OpenLoopControllerSim_1_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (OpenLoopControllerSim_1_DW.HILInitialize_Card,
         OpenLoopControllerSim_1_P.HILInitialize_AOChannels, 8U,
         &OpenLoopControllerSim_1_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(OpenLoopControllerSim_1_M, _rt_error_message);
        return;
      }
    }

    if ((OpenLoopControllerSim_1_P.HILInitialize_EIPStart && !is_switching) ||
        (OpenLoopControllerSim_1_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &OpenLoopControllerSim_1_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] =
            OpenLoopControllerSim_1_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (OpenLoopControllerSim_1_DW.HILInitialize_Card,
         OpenLoopControllerSim_1_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &OpenLoopControllerSim_1_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(OpenLoopControllerSim_1_M, _rt_error_message);
        return;
      }
    }

    if ((OpenLoopControllerSim_1_P.HILInitialize_EIStart && !is_switching) ||
        (OpenLoopControllerSim_1_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &OpenLoopControllerSim_1_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] =
            OpenLoopControllerSim_1_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts
        (OpenLoopControllerSim_1_DW.HILInitialize_Card,
         OpenLoopControllerSim_1_P.HILInitialize_EIChannels, 8U,
         &OpenLoopControllerSim_1_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(OpenLoopControllerSim_1_M, _rt_error_message);
        return;
      }
    }

    if ((OpenLoopControllerSim_1_P.HILInitialize_POPStart && !is_switching) ||
        (OpenLoopControllerSim_1_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &OpenLoopControllerSim_1_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = OpenLoopControllerSim_1_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(OpenLoopControllerSim_1_DW.HILInitialize_Card,
        OpenLoopControllerSim_1_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &OpenLoopControllerSim_1_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(OpenLoopControllerSim_1_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          OpenLoopControllerSim_1_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues =
          &OpenLoopControllerSim_1_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            OpenLoopControllerSim_1_DW.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = (p_HILInitialize_POChannels[i1]);
            OpenLoopControllerSim_1_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = OpenLoopControllerSim_1_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            OpenLoopControllerSim_1_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = (p_HILInitialize_POChannels[i1]);
            OpenLoopControllerSim_1_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] =
              OpenLoopControllerSim_1_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency
          (OpenLoopControllerSim_1_DW.HILInitialize_Card,
           &OpenLoopControllerSim_1_DW.HILInitialize_POSortedChans[0],
           num_duty_cycle_modes,
           &OpenLoopControllerSim_1_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(OpenLoopControllerSim_1_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle
          (OpenLoopControllerSim_1_DW.HILInitialize_Card,
           &OpenLoopControllerSim_1_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
           num_frequency_modes,
           &OpenLoopControllerSim_1_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(OpenLoopControllerSim_1_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &OpenLoopControllerSim_1_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] =
            OpenLoopControllerSim_1_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &OpenLoopControllerSim_1_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] =
            OpenLoopControllerSim_1_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &OpenLoopControllerSim_1_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] =
            OpenLoopControllerSim_1_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration
        (OpenLoopControllerSim_1_DW.HILInitialize_Card,
         OpenLoopControllerSim_1_P.HILInitialize_POChannels, 8U,
         (t_pwm_configuration *)
         &OpenLoopControllerSim_1_DW.HILInitialize_POModeValues[0],
         (t_pwm_alignment *)
         &OpenLoopControllerSim_1_DW.HILInitialize_POAlignValues[0],
         (t_pwm_polarity *)
         &OpenLoopControllerSim_1_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(OpenLoopControllerSim_1_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &OpenLoopControllerSim_1_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] =
            OpenLoopControllerSim_1_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues =
          &OpenLoopControllerSim_1_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = OpenLoopControllerSim_1_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband
        (OpenLoopControllerSim_1_DW.HILInitialize_Card,
         OpenLoopControllerSim_1_P.HILInitialize_POChannels, 8U,
         &OpenLoopControllerSim_1_DW.HILInitialize_POSortedFreqs[0],
         &OpenLoopControllerSim_1_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(OpenLoopControllerSim_1_M, _rt_error_message);
        return;
      }
    }

    if ((OpenLoopControllerSim_1_P.HILInitialize_POStart && !is_switching) ||
        (OpenLoopControllerSim_1_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues =
          &OpenLoopControllerSim_1_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = OpenLoopControllerSim_1_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(OpenLoopControllerSim_1_DW.HILInitialize_Card,
        OpenLoopControllerSim_1_P.HILInitialize_POChannels, 8U,
        &OpenLoopControllerSim_1_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(OpenLoopControllerSim_1_M, _rt_error_message);
        return;
      }
    }

    if (OpenLoopControllerSim_1_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues =
          &OpenLoopControllerSim_1_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = OpenLoopControllerSim_1_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (OpenLoopControllerSim_1_DW.HILInitialize_Card,
         OpenLoopControllerSim_1_P.HILInitialize_POChannels, 8U,
         &OpenLoopControllerSim_1_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(OpenLoopControllerSim_1_M, _rt_error_message);
        return;
      }
    }
  }

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  OpenLoopControllerSim_1_X.TransferFcn_CSTATE = 0.0;
}

/* Model terminate function */
void OpenLoopControllerSim_1_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: OpenLoopControllerSim_1/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(OpenLoopControllerSim_1_DW.HILInitialize_Card);
    hil_monitor_stop_all(OpenLoopControllerSim_1_DW.HILInitialize_Card);
    is_switching = false;
    if ((OpenLoopControllerSim_1_P.HILInitialize_AOTerminate && !is_switching) ||
        (OpenLoopControllerSim_1_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &OpenLoopControllerSim_1_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = OpenLoopControllerSim_1_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((OpenLoopControllerSim_1_P.HILInitialize_POTerminate && !is_switching) ||
        (OpenLoopControllerSim_1_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues =
          &OpenLoopControllerSim_1_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = OpenLoopControllerSim_1_P.HILInitialize_POFinal;
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
      result = hil_write(OpenLoopControllerSim_1_DW.HILInitialize_Card
                         , OpenLoopControllerSim_1_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , OpenLoopControllerSim_1_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &OpenLoopControllerSim_1_DW.HILInitialize_AOVoltages
                         [0]
                         , &OpenLoopControllerSim_1_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog
            (OpenLoopControllerSim_1_DW.HILInitialize_Card,
             OpenLoopControllerSim_1_P.HILInitialize_AOChannels,
             num_final_analog_outputs,
             &OpenLoopControllerSim_1_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm
            (OpenLoopControllerSim_1_DW.HILInitialize_Card,
             OpenLoopControllerSim_1_P.HILInitialize_POChannels,
             num_final_pwm_outputs,
             &OpenLoopControllerSim_1_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(OpenLoopControllerSim_1_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(OpenLoopControllerSim_1_DW.HILInitialize_Card);
    hil_monitor_delete_all(OpenLoopControllerSim_1_DW.HILInitialize_Card);
    hil_close(OpenLoopControllerSim_1_DW.HILInitialize_Card);
    OpenLoopControllerSim_1_DW.HILInitialize_Card = NULL;
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
  OpenLoopControllerSim_1_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  OpenLoopControllerSim_1_update();
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
  OpenLoopControllerSim_1_initialize();
}

void MdlTerminate(void)
{
  OpenLoopControllerSim_1_terminate();
}

/* Registration function */
RT_MODEL_OpenLoopControllerSi_T *OpenLoopControllerSim_1(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)OpenLoopControllerSim_1_M, 0,
                sizeof(RT_MODEL_OpenLoopControllerSi_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&OpenLoopControllerSim_1_M->solverInfo,
                          &OpenLoopControllerSim_1_M->Timing.simTimeStep);
    rtsiSetTPtr(&OpenLoopControllerSim_1_M->solverInfo, &rtmGetTPtr
                (OpenLoopControllerSim_1_M));
    rtsiSetStepSizePtr(&OpenLoopControllerSim_1_M->solverInfo,
                       &OpenLoopControllerSim_1_M->Timing.stepSize0);
    rtsiSetdXPtr(&OpenLoopControllerSim_1_M->solverInfo,
                 &OpenLoopControllerSim_1_M->derivs);
    rtsiSetContStatesPtr(&OpenLoopControllerSim_1_M->solverInfo, (real_T **)
                         &OpenLoopControllerSim_1_M->contStates);
    rtsiSetNumContStatesPtr(&OpenLoopControllerSim_1_M->solverInfo,
      &OpenLoopControllerSim_1_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&OpenLoopControllerSim_1_M->solverInfo,
      &OpenLoopControllerSim_1_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&OpenLoopControllerSim_1_M->solverInfo,
      &OpenLoopControllerSim_1_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&OpenLoopControllerSim_1_M->solverInfo,
      &OpenLoopControllerSim_1_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&OpenLoopControllerSim_1_M->solverInfo,
                          (&rtmGetErrorStatus(OpenLoopControllerSim_1_M)));
    rtsiSetRTModelPtr(&OpenLoopControllerSim_1_M->solverInfo,
                      OpenLoopControllerSim_1_M);
  }

  rtsiSetSimTimeStep(&OpenLoopControllerSim_1_M->solverInfo, MAJOR_TIME_STEP);
  OpenLoopControllerSim_1_M->intgData.y = OpenLoopControllerSim_1_M->odeY;
  OpenLoopControllerSim_1_M->intgData.f[0] = OpenLoopControllerSim_1_M->odeF[0];
  OpenLoopControllerSim_1_M->intgData.f[1] = OpenLoopControllerSim_1_M->odeF[1];
  OpenLoopControllerSim_1_M->intgData.f[2] = OpenLoopControllerSim_1_M->odeF[2];
  OpenLoopControllerSim_1_M->contStates = ((real_T *) &OpenLoopControllerSim_1_X);
  rtsiSetSolverData(&OpenLoopControllerSim_1_M->solverInfo, (void *)
                    &OpenLoopControllerSim_1_M->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&OpenLoopControllerSim_1_M->solverInfo,
    false);
  rtsiSetSolverName(&OpenLoopControllerSim_1_M->solverInfo,"ode3");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = OpenLoopControllerSim_1_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "OpenLoopControllerSim_1_M points to
       static memory which is guaranteed to be non-NULL" */
    OpenLoopControllerSim_1_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    OpenLoopControllerSim_1_M->Timing.sampleTimes =
      (&OpenLoopControllerSim_1_M->Timing.sampleTimesArray[0]);
    OpenLoopControllerSim_1_M->Timing.offsetTimes =
      (&OpenLoopControllerSim_1_M->Timing.offsetTimesArray[0]);

    /* task periods */
    OpenLoopControllerSim_1_M->Timing.sampleTimes[0] = (0.0);
    OpenLoopControllerSim_1_M->Timing.sampleTimes[1] = (0.001);

    /* task offsets */
    OpenLoopControllerSim_1_M->Timing.offsetTimes[0] = (0.0);
    OpenLoopControllerSim_1_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(OpenLoopControllerSim_1_M,
             &OpenLoopControllerSim_1_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = OpenLoopControllerSim_1_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    OpenLoopControllerSim_1_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(OpenLoopControllerSim_1_M, 4.0);
  OpenLoopControllerSim_1_M->Timing.stepSize0 = 0.001;
  OpenLoopControllerSim_1_M->Timing.stepSize1 = 0.001;

  /* External mode info */
  OpenLoopControllerSim_1_M->Sizes.checksums[0] = (2883306664U);
  OpenLoopControllerSim_1_M->Sizes.checksums[1] = (3375633093U);
  OpenLoopControllerSim_1_M->Sizes.checksums[2] = (4161203017U);
  OpenLoopControllerSim_1_M->Sizes.checksums[3] = (1210622026U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    OpenLoopControllerSim_1_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(OpenLoopControllerSim_1_M->extModeInfo,
      &OpenLoopControllerSim_1_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(OpenLoopControllerSim_1_M->extModeInfo,
                        OpenLoopControllerSim_1_M->Sizes.checksums);
    rteiSetTPtr(OpenLoopControllerSim_1_M->extModeInfo, rtmGetTPtr
                (OpenLoopControllerSim_1_M));
  }

  OpenLoopControllerSim_1_M->solverInfoPtr =
    (&OpenLoopControllerSim_1_M->solverInfo);
  OpenLoopControllerSim_1_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&OpenLoopControllerSim_1_M->solverInfo, 0.001);
  rtsiSetSolverMode(&OpenLoopControllerSim_1_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  OpenLoopControllerSim_1_M->blockIO = ((void *) &OpenLoopControllerSim_1_B);
  (void) memset(((void *) &OpenLoopControllerSim_1_B), 0,
                sizeof(B_OpenLoopControllerSim_1_T));

  /* parameters */
  OpenLoopControllerSim_1_M->defaultParam = ((real_T *)
    &OpenLoopControllerSim_1_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &OpenLoopControllerSim_1_X;
    OpenLoopControllerSim_1_M->contStates = (x);
    (void) memset((void *)&OpenLoopControllerSim_1_X, 0,
                  sizeof(X_OpenLoopControllerSim_1_T));
  }

  /* states (dwork) */
  OpenLoopControllerSim_1_M->dwork = ((void *) &OpenLoopControllerSim_1_DW);
  (void) memset((void *)&OpenLoopControllerSim_1_DW, 0,
                sizeof(DW_OpenLoopControllerSim_1_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    OpenLoopControllerSim_1_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 19;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  OpenLoopControllerSim_1_M->Sizes.numContStates = (1);/* Number of continuous states */
  OpenLoopControllerSim_1_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  OpenLoopControllerSim_1_M->Sizes.numY = (0);/* Number of model outputs */
  OpenLoopControllerSim_1_M->Sizes.numU = (0);/* Number of model inputs */
  OpenLoopControllerSim_1_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  OpenLoopControllerSim_1_M->Sizes.numSampTimes = (2);/* Number of sample times */
  OpenLoopControllerSim_1_M->Sizes.numBlocks = (5);/* Number of blocks */
  OpenLoopControllerSim_1_M->Sizes.numBlockIO = (2);/* Number of block outputs */
  OpenLoopControllerSim_1_M->Sizes.numBlockPrms = (98);/* Sum of parameter "widths" */
  return OpenLoopControllerSim_1_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/

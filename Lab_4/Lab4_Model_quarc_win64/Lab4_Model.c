/*
 * Lab4_Model.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Lab4_Model".
 *
 * Model version              : 7.0
 * Simulink Coder version : 9.7 (R2022a) 13-Nov-2021
 * C source code generated on : Tue Sep 20 12:15:05 2022
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Lab4_Model.h"
#include "rtwtypes.h"
#include "Lab4_Model_private.h"
#include "rt_nonfinite.h"
#include "Lab4_Model_dt.h"

/* Block signals (default storage) */
B_Lab4_Model_T Lab4_Model_B;

/* Block states (default storage) */
DW_Lab4_Model_T Lab4_Model_DW;

/* Real-time model */
static RT_MODEL_Lab4_Model_T Lab4_Model_M_;
RT_MODEL_Lab4_Model_T *const Lab4_Model_M = &Lab4_Model_M_;

/* Model output function */
void Lab4_Model_output(void)
{
  real_T rtb_HILReadOther;

  /* Saturate: '<Root>/Saturation' incorporates:
   *  Constant: '<Root>/Constant'
   */
  if (Lab4_Model_P.Constant_Value > Lab4_Model_P.Saturation_UpperSat) {
    rtb_HILReadOther = Lab4_Model_P.Saturation_UpperSat;
  } else if (Lab4_Model_P.Constant_Value < Lab4_Model_P.Saturation_LowerSat) {
    rtb_HILReadOther = Lab4_Model_P.Saturation_LowerSat;
  } else {
    rtb_HILReadOther = Lab4_Model_P.Constant_Value;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* S-Function (hil_write_analog_block): '<Root>/HIL Write Analog' */

  /* S-Function Block: Lab4_Model/HIL Write Analog (hil_write_analog_block) */
  {
    t_error result;
    result = hil_write_analog(Lab4_Model_DW.HILInitialize_Card,
      &Lab4_Model_P.HILWriteAnalog_channels, 1, &rtb_HILReadOther);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab4_Model_M, _rt_error_message);
    }
  }

  /* S-Function (hil_read_other_block): '<Root>/HIL Read Other' */

  /* S-Function Block: Lab4_Model/HIL Read Other (hil_read_other_block) */
  {
    t_error result = hil_read_other(Lab4_Model_DW.HILInitialize_Card,
      &Lab4_Model_P.HILReadOther_channels, 1, &Lab4_Model_DW.HILReadOther_Buffer);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab4_Model_M, _rt_error_message);
    }

    rtb_HILReadOther = Lab4_Model_DW.HILReadOther_Buffer;
  }

  /* Gain: '<Root>/Gain' */
  Lab4_Model_B.Gain = Lab4_Model_P.Gain_Gain * rtb_HILReadOther;
}

/* Model update function */
void Lab4_Model_update(void)
{
  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Lab4_Model_M->Timing.clockTick0)) {
    ++Lab4_Model_M->Timing.clockTickH0;
  }

  Lab4_Model_M->Timing.t[0] = Lab4_Model_M->Timing.clockTick0 *
    Lab4_Model_M->Timing.stepSize0 + Lab4_Model_M->Timing.clockTickH0 *
    Lab4_Model_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void Lab4_Model_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Lab4_Model/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &Lab4_Model_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab4_Model_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(Lab4_Model_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab4_Model_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(Lab4_Model_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab4_Model_M, _rt_error_message);
      return;
    }

    if ((Lab4_Model_P.HILInitialize_AIPStart && !is_switching) ||
        (Lab4_Model_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &Lab4_Model_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (Lab4_Model_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &Lab4_Model_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = Lab4_Model_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(Lab4_Model_DW.HILInitialize_Card,
        Lab4_Model_P.HILInitialize_AIChannels, 8U,
        &Lab4_Model_DW.HILInitialize_AIMinimums[0],
        &Lab4_Model_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab4_Model_M, _rt_error_message);
        return;
      }
    }

    if ((Lab4_Model_P.HILInitialize_AOPStart && !is_switching) ||
        (Lab4_Model_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &Lab4_Model_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (Lab4_Model_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &Lab4_Model_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = Lab4_Model_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges(Lab4_Model_DW.HILInitialize_Card,
        Lab4_Model_P.HILInitialize_AOChannels, 8U,
        &Lab4_Model_DW.HILInitialize_AOMinimums[0],
        &Lab4_Model_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab4_Model_M, _rt_error_message);
        return;
      }
    }

    if ((Lab4_Model_P.HILInitialize_AOStart && !is_switching) ||
        (Lab4_Model_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Lab4_Model_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab4_Model_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(Lab4_Model_DW.HILInitialize_Card,
        Lab4_Model_P.HILInitialize_AOChannels, 8U,
        &Lab4_Model_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab4_Model_M, _rt_error_message);
        return;
      }
    }

    if (Lab4_Model_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Lab4_Model_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab4_Model_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (Lab4_Model_DW.HILInitialize_Card, Lab4_Model_P.HILInitialize_AOChannels,
         8U, &Lab4_Model_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab4_Model_M, _rt_error_message);
        return;
      }
    }

    if ((Lab4_Model_P.HILInitialize_EIPStart && !is_switching) ||
        (Lab4_Model_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &Lab4_Model_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = Lab4_Model_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(Lab4_Model_DW.HILInitialize_Card,
        Lab4_Model_P.HILInitialize_EIChannels, 8U, (t_encoder_quadrature_mode *)
        &Lab4_Model_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab4_Model_M, _rt_error_message);
        return;
      }
    }

    if ((Lab4_Model_P.HILInitialize_EIStart && !is_switching) ||
        (Lab4_Model_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &Lab4_Model_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = Lab4_Model_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(Lab4_Model_DW.HILInitialize_Card,
        Lab4_Model_P.HILInitialize_EIChannels, 8U,
        &Lab4_Model_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab4_Model_M, _rt_error_message);
        return;
      }
    }

    if ((Lab4_Model_P.HILInitialize_POPStart && !is_switching) ||
        (Lab4_Model_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &Lab4_Model_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = Lab4_Model_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(Lab4_Model_DW.HILInitialize_Card,
        Lab4_Model_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &Lab4_Model_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab4_Model_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          Lab4_Model_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues = &Lab4_Model_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            Lab4_Model_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              (p_HILInitialize_POChannels[i1]);
            Lab4_Model_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              Lab4_Model_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            Lab4_Model_DW.HILInitialize_POSortedChans[7U - num_frequency_modes] =
              (p_HILInitialize_POChannels[i1]);
            Lab4_Model_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes] =
              Lab4_Model_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(Lab4_Model_DW.HILInitialize_Card,
          &Lab4_Model_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &Lab4_Model_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab4_Model_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(Lab4_Model_DW.HILInitialize_Card,
          &Lab4_Model_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &Lab4_Model_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab4_Model_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &Lab4_Model_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = Lab4_Model_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &Lab4_Model_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = Lab4_Model_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &Lab4_Model_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = Lab4_Model_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(Lab4_Model_DW.HILInitialize_Card,
        Lab4_Model_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &Lab4_Model_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &Lab4_Model_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &Lab4_Model_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab4_Model_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &Lab4_Model_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = Lab4_Model_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &Lab4_Model_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab4_Model_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(Lab4_Model_DW.HILInitialize_Card,
        Lab4_Model_P.HILInitialize_POChannels, 8U,
        &Lab4_Model_DW.HILInitialize_POSortedFreqs[0],
        &Lab4_Model_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab4_Model_M, _rt_error_message);
        return;
      }
    }

    if ((Lab4_Model_P.HILInitialize_POStart && !is_switching) ||
        (Lab4_Model_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab4_Model_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab4_Model_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(Lab4_Model_DW.HILInitialize_Card,
        Lab4_Model_P.HILInitialize_POChannels, 8U,
        &Lab4_Model_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab4_Model_M, _rt_error_message);
        return;
      }
    }

    if (Lab4_Model_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab4_Model_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab4_Model_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (Lab4_Model_DW.HILInitialize_Card, Lab4_Model_P.HILInitialize_POChannels,
         8U, &Lab4_Model_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab4_Model_M, _rt_error_message);
        return;
      }
    }
  }
}

/* Model terminate function */
void Lab4_Model_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Lab4_Model/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(Lab4_Model_DW.HILInitialize_Card);
    hil_monitor_stop_all(Lab4_Model_DW.HILInitialize_Card);
    is_switching = false;
    if ((Lab4_Model_P.HILInitialize_AOTerminate && !is_switching) ||
        (Lab4_Model_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Lab4_Model_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab4_Model_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((Lab4_Model_P.HILInitialize_POTerminate && !is_switching) ||
        (Lab4_Model_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab4_Model_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab4_Model_P.HILInitialize_POFinal;
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
      result = hil_write(Lab4_Model_DW.HILInitialize_Card
                         , Lab4_Model_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , Lab4_Model_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &Lab4_Model_DW.HILInitialize_AOVoltages[0]
                         , &Lab4_Model_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(Lab4_Model_DW.HILInitialize_Card,
            Lab4_Model_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &Lab4_Model_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(Lab4_Model_DW.HILInitialize_Card,
            Lab4_Model_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &Lab4_Model_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab4_Model_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(Lab4_Model_DW.HILInitialize_Card);
    hil_monitor_delete_all(Lab4_Model_DW.HILInitialize_Card);
    hil_close(Lab4_Model_DW.HILInitialize_Card);
    Lab4_Model_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  Lab4_Model_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  Lab4_Model_update();
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
  Lab4_Model_initialize();
}

void MdlTerminate(void)
{
  Lab4_Model_terminate();
}

/* Registration function */
RT_MODEL_Lab4_Model_T *Lab4_Model(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Lab4_Model_M, 0,
                sizeof(RT_MODEL_Lab4_Model_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Lab4_Model_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "Lab4_Model_M points to
       static memory which is guaranteed to be non-NULL" */
    Lab4_Model_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Lab4_Model_M->Timing.sampleTimes = (&Lab4_Model_M->Timing.sampleTimesArray[0]);
    Lab4_Model_M->Timing.offsetTimes = (&Lab4_Model_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Lab4_Model_M->Timing.sampleTimes[0] = (0.001);

    /* task offsets */
    Lab4_Model_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(Lab4_Model_M, &Lab4_Model_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Lab4_Model_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    Lab4_Model_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Lab4_Model_M, 2.0);
  Lab4_Model_M->Timing.stepSize0 = 0.001;

  /* External mode info */
  Lab4_Model_M->Sizes.checksums[0] = (3030831473U);
  Lab4_Model_M->Sizes.checksums[1] = (3813911309U);
  Lab4_Model_M->Sizes.checksums[2] = (2403750882U);
  Lab4_Model_M->Sizes.checksums[3] = (2831308334U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    Lab4_Model_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Lab4_Model_M->extModeInfo,
      &Lab4_Model_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Lab4_Model_M->extModeInfo, Lab4_Model_M->Sizes.checksums);
    rteiSetTPtr(Lab4_Model_M->extModeInfo, rtmGetTPtr(Lab4_Model_M));
  }

  Lab4_Model_M->solverInfoPtr = (&Lab4_Model_M->solverInfo);
  Lab4_Model_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&Lab4_Model_M->solverInfo, 0.001);
  rtsiSetSolverMode(&Lab4_Model_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  Lab4_Model_M->blockIO = ((void *) &Lab4_Model_B);
  (void) memset(((void *) &Lab4_Model_B), 0,
                sizeof(B_Lab4_Model_T));

  /* parameters */
  Lab4_Model_M->defaultParam = ((real_T *)&Lab4_Model_P);

  /* states (dwork) */
  Lab4_Model_M->dwork = ((void *) &Lab4_Model_DW);
  (void) memset((void *)&Lab4_Model_DW, 0,
                sizeof(DW_Lab4_Model_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    Lab4_Model_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 19;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  Lab4_Model_M->Sizes.numContStates = (0);/* Number of continuous states */
  Lab4_Model_M->Sizes.numY = (0);      /* Number of model outputs */
  Lab4_Model_M->Sizes.numU = (0);      /* Number of model inputs */
  Lab4_Model_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  Lab4_Model_M->Sizes.numSampTimes = (1);/* Number of sample times */
  Lab4_Model_M->Sizes.numBlocks = (8); /* Number of blocks */
  Lab4_Model_M->Sizes.numBlockIO = (1);/* Number of block outputs */
  Lab4_Model_M->Sizes.numBlockPrms = (102);/* Sum of parameter "widths" */
  return Lab4_Model_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/

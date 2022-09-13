/*
 * Lab2.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Lab2".
 *
 * Model version              : 7.2
 * Simulink Coder version : 9.7 (R2022a) 13-Nov-2021
 * C source code generated on : Tue Sep 13 12:48:50 2022
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Lab2.h"
#include "rtwtypes.h"
#include "Lab2_private.h"
#include "rt_nonfinite.h"
#include "Lab2_dt.h"

/* Block signals (default storage) */
B_Lab2_T Lab2_B;

/* Block states (default storage) */
DW_Lab2_T Lab2_DW;

/* Real-time model */
static RT_MODEL_Lab2_T Lab2_M_;
RT_MODEL_Lab2_T *const Lab2_M = &Lab2_M_;

/* Model output function */
void Lab2_output(void)
{
  /* local block i/o variables */
  real_T rtb_HILReadAnalog_o1;
  real_T rtb_HILReadAnalog_o2;

  /* S-Function (hil_write_analog_block): '<Root>/HIL Write Analog' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant1'
   */

  /* S-Function Block: Lab2/HIL Write Analog (hil_write_analog_block) */
  {
    t_error result;
    Lab2_DW.HILWriteAnalog_Buffer[0] = Lab2_P.Constant_Value;
    Lab2_DW.HILWriteAnalog_Buffer[1] = Lab2_P.Constant1_Value;
    result = hil_write_analog(Lab2_DW.HILInitialize_Card,
      Lab2_P.HILWriteAnalog_channels, 2, &Lab2_DW.HILWriteAnalog_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab2_M, _rt_error_message);
    }
  }

  /* S-Function (hil_read_analog_block): '<Root>/HIL Read Analog' */

  /* S-Function Block: Lab2/HIL Read Analog (hil_read_analog_block) */
  {
    t_error result = hil_read_analog(Lab2_DW.HILInitialize_Card,
      Lab2_P.HILReadAnalog_channels, 2, &Lab2_DW.HILReadAnalog_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab2_M, _rt_error_message);
    }

    rtb_HILReadAnalog_o1 = Lab2_DW.HILReadAnalog_Buffer[0];
    rtb_HILReadAnalog_o2 = Lab2_DW.HILReadAnalog_Buffer[1];
  }

  /* MATLAB Function: '<Root>/Pendulum Calibration' */
  Lab2_B.y_n = 16.462216 * rtb_HILReadAnalog_o2 - 0.667143;

  /* MATLAB Function: '<Root>/Slider Calibration' */
  Lab2_B.y = rtb_HILReadAnalog_o1 * 0.52948 - 0.720456;
}

/* Model update function */
void Lab2_update(void)
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
  if (!(++Lab2_M->Timing.clockTick0)) {
    ++Lab2_M->Timing.clockTickH0;
  }

  Lab2_M->Timing.t[0] = Lab2_M->Timing.clockTick0 * Lab2_M->Timing.stepSize0 +
    Lab2_M->Timing.clockTickH0 * Lab2_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void Lab2_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Lab2/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &Lab2_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab2_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(Lab2_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab2_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(Lab2_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab2_M, _rt_error_message);
      return;
    }

    if ((Lab2_P.HILInitialize_AIPStart && !is_switching) ||
        (Lab2_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &Lab2_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (Lab2_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &Lab2_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = Lab2_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(Lab2_DW.HILInitialize_Card,
        Lab2_P.HILInitialize_AIChannels, 8U,
        &Lab2_DW.HILInitialize_AIMinimums[0], &Lab2_DW.HILInitialize_AIMaximums
        [0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab2_M, _rt_error_message);
        return;
      }
    }

    if ((Lab2_P.HILInitialize_AOPStart && !is_switching) ||
        (Lab2_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &Lab2_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (Lab2_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &Lab2_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = Lab2_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges(Lab2_DW.HILInitialize_Card,
        Lab2_P.HILInitialize_AOChannels, 8U,
        &Lab2_DW.HILInitialize_AOMinimums[0], &Lab2_DW.HILInitialize_AOMaximums
        [0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab2_M, _rt_error_message);
        return;
      }
    }

    if ((Lab2_P.HILInitialize_AOStart && !is_switching) ||
        (Lab2_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Lab2_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab2_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(Lab2_DW.HILInitialize_Card,
        Lab2_P.HILInitialize_AOChannels, 8U, &Lab2_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab2_M, _rt_error_message);
        return;
      }
    }

    if (Lab2_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Lab2_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab2_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (Lab2_DW.HILInitialize_Card, Lab2_P.HILInitialize_AOChannels, 8U,
         &Lab2_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab2_M, _rt_error_message);
        return;
      }
    }

    if ((Lab2_P.HILInitialize_EIPStart && !is_switching) ||
        (Lab2_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes = &Lab2_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = Lab2_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(Lab2_DW.HILInitialize_Card,
        Lab2_P.HILInitialize_EIChannels, 8U, (t_encoder_quadrature_mode *)
        &Lab2_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab2_M, _rt_error_message);
        return;
      }
    }

    if ((Lab2_P.HILInitialize_EIStart && !is_switching) ||
        (Lab2_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts = &Lab2_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = Lab2_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(Lab2_DW.HILInitialize_Card,
        Lab2_P.HILInitialize_EIChannels, 8U,
        &Lab2_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab2_M, _rt_error_message);
        return;
      }
    }

    if ((Lab2_P.HILInitialize_POPStart && !is_switching) ||
        (Lab2_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &Lab2_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = Lab2_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(Lab2_DW.HILInitialize_Card,
        Lab2_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &Lab2_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab2_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          Lab2_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues = &Lab2_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            Lab2_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              (p_HILInitialize_POChannels[i1]);
            Lab2_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              Lab2_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            Lab2_DW.HILInitialize_POSortedChans[7U - num_frequency_modes] =
              (p_HILInitialize_POChannels[i1]);
            Lab2_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes] =
              Lab2_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(Lab2_DW.HILInitialize_Card,
          &Lab2_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &Lab2_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab2_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(Lab2_DW.HILInitialize_Card,
          &Lab2_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &Lab2_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab2_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &Lab2_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = Lab2_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &Lab2_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = Lab2_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals = &Lab2_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = Lab2_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(Lab2_DW.HILInitialize_Card,
        Lab2_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &Lab2_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &Lab2_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &Lab2_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab2_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &Lab2_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = Lab2_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &Lab2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab2_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(Lab2_DW.HILInitialize_Card,
        Lab2_P.HILInitialize_POChannels, 8U,
        &Lab2_DW.HILInitialize_POSortedFreqs[0],
        &Lab2_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab2_M, _rt_error_message);
        return;
      }
    }

    if ((Lab2_P.HILInitialize_POStart && !is_switching) ||
        (Lab2_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab2_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(Lab2_DW.HILInitialize_Card,
        Lab2_P.HILInitialize_POChannels, 8U, &Lab2_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab2_M, _rt_error_message);
        return;
      }
    }

    if (Lab2_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab2_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state(Lab2_DW.HILInitialize_Card,
        Lab2_P.HILInitialize_POChannels, 8U, &Lab2_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab2_M, _rt_error_message);
        return;
      }
    }
  }
}

/* Model terminate function */
void Lab2_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Lab2/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(Lab2_DW.HILInitialize_Card);
    hil_monitor_stop_all(Lab2_DW.HILInitialize_Card);
    is_switching = false;
    if ((Lab2_P.HILInitialize_AOTerminate && !is_switching) ||
        (Lab2_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Lab2_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab2_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((Lab2_P.HILInitialize_POTerminate && !is_switching) ||
        (Lab2_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab2_P.HILInitialize_POFinal;
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
      result = hil_write(Lab2_DW.HILInitialize_Card
                         , Lab2_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , Lab2_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &Lab2_DW.HILInitialize_AOVoltages[0]
                         , &Lab2_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(Lab2_DW.HILInitialize_Card,
            Lab2_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &Lab2_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(Lab2_DW.HILInitialize_Card,
            Lab2_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &Lab2_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab2_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(Lab2_DW.HILInitialize_Card);
    hil_monitor_delete_all(Lab2_DW.HILInitialize_Card);
    hil_close(Lab2_DW.HILInitialize_Card);
    Lab2_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  Lab2_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  Lab2_update();
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
  Lab2_initialize();
}

void MdlTerminate(void)
{
  Lab2_terminate();
}

/* Registration function */
RT_MODEL_Lab2_T *Lab2(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Lab2_M, 0,
                sizeof(RT_MODEL_Lab2_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Lab2_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "Lab2_M points to
       static memory which is guaranteed to be non-NULL" */
    Lab2_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Lab2_M->Timing.sampleTimes = (&Lab2_M->Timing.sampleTimesArray[0]);
    Lab2_M->Timing.offsetTimes = (&Lab2_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Lab2_M->Timing.sampleTimes[0] = (0.001);

    /* task offsets */
    Lab2_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(Lab2_M, &Lab2_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Lab2_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    Lab2_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Lab2_M, 45.0);
  Lab2_M->Timing.stepSize0 = 0.001;

  /* External mode info */
  Lab2_M->Sizes.checksums[0] = (3841919626U);
  Lab2_M->Sizes.checksums[1] = (2639007391U);
  Lab2_M->Sizes.checksums[2] = (2283905476U);
  Lab2_M->Sizes.checksums[3] = (974154560U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[3];
    Lab2_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Lab2_M->extModeInfo,
      &Lab2_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Lab2_M->extModeInfo, Lab2_M->Sizes.checksums);
    rteiSetTPtr(Lab2_M->extModeInfo, rtmGetTPtr(Lab2_M));
  }

  Lab2_M->solverInfoPtr = (&Lab2_M->solverInfo);
  Lab2_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&Lab2_M->solverInfo, 0.001);
  rtsiSetSolverMode(&Lab2_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  Lab2_M->blockIO = ((void *) &Lab2_B);
  (void) memset(((void *) &Lab2_B), 0,
                sizeof(B_Lab2_T));

  /* parameters */
  Lab2_M->defaultParam = ((real_T *)&Lab2_P);

  /* states (dwork) */
  Lab2_M->dwork = ((void *) &Lab2_DW);
  (void) memset((void *)&Lab2_DW, 0,
                sizeof(DW_Lab2_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    Lab2_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 19;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  Lab2_M->Sizes.numContStates = (0);   /* Number of continuous states */
  Lab2_M->Sizes.numY = (0);            /* Number of model outputs */
  Lab2_M->Sizes.numU = (0);            /* Number of model inputs */
  Lab2_M->Sizes.sysDirFeedThru = (0);  /* The model is not direct feedthrough */
  Lab2_M->Sizes.numSampTimes = (1);    /* Number of sample times */
  Lab2_M->Sizes.numBlocks = (13);      /* Number of blocks */
  Lab2_M->Sizes.numBlockIO = (2);      /* Number of block outputs */
  Lab2_M->Sizes.numBlockPrms = (102);  /* Sum of parameter "widths" */
  return Lab2_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/

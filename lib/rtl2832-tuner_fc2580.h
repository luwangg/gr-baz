#ifndef __TUNER_FC2580_H
#define __TUNER_FC2580_H

#include "rtl2832.h"

namespace RTL2832_NAMESPACE
{
namespace TUNERS_NAMESPACE
{

class fc2580 : public RTL2832_NAMESPACE::tuner_skeleton
{
IMPLEMENT_INLINE_TUNER_FACTORY(fc2580)
public:
	fc2580(demod* p);
public:
	inline virtual const char* name() const
	{ return "Fitipower FC2580"; }
public:
	int initialise(tuner::PPARAMS params = NULL);
	int set_frequency(double freq);
	int set_bandwidth(double bw);
	int set_gain(double gain);
};

}
}

#define	BORDER_FREQ	2600000	//2.6GHz : The border frequency which determines whether Low VCO or High VCO is used
#define USE_EXT_CLK	0	//0 : Use internal XTAL Oscillator / 1 : Use External Clock input
#define OFS_RSSI 57

#define FC2580_I2C_ADDR		0xac
#define FC2580_CHECK_ADDR	0x01
#define FC2580_CHECK_VAL	0x56

typedef enum {
	FC2580_UHF_BAND,
	FC2580_L_BAND,
	FC2580_VHF_BAND,
	FC2580_NO_BAND
} fc2580_band_type;

typedef int fc2580_fci_result_type;

#define FC2580_FCI_FAIL		0
#define FC2580_FCI_SUCCESS	1

enum FUNCTION_STATUS
{
	FUNCTION_SUCCESS,
	FUNCTION_ERROR,
};

extern void fc2580_wait_msec(RTL2832_NAMESPACE::tuner* pTuner, int a);
/*
fc2580_fci_result_type fc2580_i2c_write(RTL2832_NAMESPACE::tuner* pTuner, unsigned char reg, unsigned char val);
fc2580_fci_result_type fc2580_i2c_read(RTL2832_NAMESPACE::tuner* pTuner, unsigned char reg, unsigned char *read_data);
*/
/*==============================================================================
       fc2580 initial setting

  This function is a generic function which gets called to initialize

  fc2580 in DVB-H mode or L-Band TDMB mode

  <input parameter>

  ifagc_mode
    type : integer
	1 : Internal AGC
	2 : Voltage Control Mode

==============================================================================*/
fc2580_fci_result_type fc2580_set_init(RTL2832_NAMESPACE::tuner* pTuner, int ifagc_mode, unsigned int freq_xtal );

/*==============================================================================
       fc2580 frequency setting

  This function is a generic function which gets called to change LO Frequency

  of fc2580 in DVB-H mode or L-Band TDMB mode

  <input parameter>

  f_lo
	Value of target LO Frequency in 'kHz' unit
	ex) 2.6GHz = 2600000

==============================================================================*/
fc2580_fci_result_type fc2580_set_freq(RTL2832_NAMESPACE::tuner* pTuner, unsigned int f_lo, unsigned int freq_xtal );


/*==============================================================================
       fc2580 filter BW setting

  This function is a generic function which gets called to change Bandwidth

  frequency of fc2580's channel selection filter

  <input parameter>

  filter_bw
    1 : 1.53MHz(TDMB)
	6 : 6MHz
	7 : 7MHz
	8 : 7.8MHz


==============================================================================*/
fc2580_fci_result_type fc2580_set_filter( RTL2832_NAMESPACE::tuner* pTuner, unsigned char filter_bw, unsigned int freq_xtal );

// The following context is FC2580 tuner API source code
// Definitions

// AGC mode
enum FC2580_AGC_MODE
{
	FC2580_AGC_INTERNAL = 1,
	FC2580_AGC_EXTERNAL = 2,
};


// Bandwidth mode
enum FC2580_BANDWIDTH_MODE
{
	FC2580_BANDWIDTH_1530000HZ = 1,
	FC2580_BANDWIDTH_6000000HZ = 6,
	FC2580_BANDWIDTH_7000000HZ = 7,
	FC2580_BANDWIDTH_8000000HZ = 8,
};

// Manipulaing functions
int
fc2580_Initialize(
	RTL2832_NAMESPACE::tuner* pTuner
	);

int
fc2580_SetRfFreqHz(
	RTL2832_NAMESPACE::tuner* pTuner,
	unsigned long RfFreqHz
	);

// Extra manipulaing functions
int
fc2580_SetBandwidthMode(
	RTL2832_NAMESPACE::tuner* pTuner,
	int BandwidthMode
	);

#endif

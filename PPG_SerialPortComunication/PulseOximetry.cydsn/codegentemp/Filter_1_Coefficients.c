#include "Filter_1.h"
#include "Filter_1_PVT.h"


/*******************************************************************************
* ChannelA filter coefficients.
* Filter Type is: Biquad
*******************************************************************************/

/* Renamed array for backward compatibility.
*  Should not be used in new designs.
*/
#define ChannelABiquadCoefficients Filter_1_ChannelABiquadCoefficients

/* Number of Biquad sections are: 3 */

const uint8 CYCODE Filter_1_ChannelABiquadCoefficients[Filter_1_BIQUAD_A_SIZE] = 
{
 /* Coefficients of Section 0 */
 0x30u, 0x02u, 0x00u, 0x00u, /* Section(0)_A0, 0.000133514404296875 */

 0x60u, 0x04u, 0x00u, 0x00u, /* Section(0)_A1, 0.00026702880859375 */

 0x30u, 0x02u, 0x00u, 0x00u, /* Section(0)_A2, 0.000133514404296875 */

 0xC4u, 0xBFu, 0x7Bu, 0x00u, /* Section(0)_B1, -1.93357944488525 */

 0x3Du, 0x1Du, 0xC4u, 0x00u, /* Section(0)_B2, 0.935715436935425 */

 /* Coefficients of Section 1 */
 0xAEu, 0x08u, 0x00u, 0x00u, /* Section(1)_A0, 0.000529766082763672 */

 0x5Du, 0x11u, 0x00u, 0x00u, /* Section(1)_A1, 0.00105977058410645 */

 0xAEu, 0x08u, 0x00u, 0x00u, /* Section(1)_A2, 0.000529766082763672 */

 0x64u, 0x4Fu, 0x7Au, 0x00u, /* Section(1)_B1, -1.91109561920166 */

 0x05u, 0x8Eu, 0xC5u, 0x00u, /* Section(1)_B2, 0.913206815719604 */

 /* Coefficients of Section 2 */
 0x97u, 0x23u, 0x00u, 0x00u, /* Section(2)_A0, 0.00217223167419434 */

 0x2Du, 0x47u, 0x00u, 0x00u, /* Section(2)_A1, 0.00434422492980957 */

 0x97u, 0x23u, 0x00u, 0x00u, /* Section(2)_A2, 0.00217223167419434 */

 0xBEu, 0x52u, 0x7Eu, 0x00u, /* Section(2)_B1, -1.97380018234253 */

 0x88u, 0x89u, 0xC1u, 0x00u, /* Section(2)_B2, 0.975980758666992 */
};


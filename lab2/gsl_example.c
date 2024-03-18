#include <stdio.h>
#include <gsl/gsl_ieee_utils.h>
#include <math.h>

int main() {
    /* Setup GSL IEEE environment */
    /* Set precision to 32 bit mode, set rounding to nearst number, disable exceptions for mantissa underflow and denormalized numbers usage*/
    gsl_ieee_set_mode(GSL_IEEE_SINGLE_PRECISION, GSL_IEEE_ROUND_TO_NEAREST, 
                        GSL_IEEE_MASK_DENORMALIZED | GSL_IEEE_MASK_UNDERFLOW);

    /* Struct holding IEEE representation of floating point numbers*/
    gsl_ieee_float_rep representation; 

    float f = 1.0; // We will start from zero and go to the smallest denormalized number

    /* nextafterf returns next float in given direction */
    f = nextafterf(f, __FLT_DENORM_MIN__);
    gsl_ieee_float_to_rep(&f, &representation);

    int i = 0;
    int ex = representation.exponent;

    /* We want to find out when our number will become denormalized */
    while(representation.type != GSL_IEEE_TYPE_DENORMAL) {
        if(i < 50) {
            /* First print out 50 next iterations with visualization of how mantissa changes */
            printf("Mantisa visualization: S: %d M: %s E: %d Type: %d Val: %.50f\n", 
                representation.sign,
                representation.mantissa, 
                representation.exponent, 
                representation.type,
                f);

            f = nextafterf(f, __FLT_DENORM_MIN__);
            gsl_ieee_float_to_rep(&f, &representation);
            i++;
        } else {
            /* Next we print out 50 exponent chhanges */
            if(representation.exponent != ex && i < 100) {
                printf("Exponent visualization: S: %d M: %s E: %d Type: %d Val: %.50f\n", 
                    representation.sign, 
                    representation.mantissa, 
                    representation.exponent, 
                    representation.type,
                    f);
                ex = representation.exponent;
                i++;
            }
        }

        /* We get next float and update our representation */
        f = nextafterf(f, __FLT_DENORM_MIN__);
        gsl_ieee_float_to_rep(&f, &representation);
    }

    /* Print out first denormalized number */
    printf("Denormal representation: S: %d M: %s E: %d Type: %d Val: %.50f \n", 
        representation.sign, 
        representation.mantissa, 
        representation.exponent, 
        representation.type, f);

    /* Now we want to find out when our number will become normalized again */
    f = nextafterf(f, 1.0f);
    gsl_ieee_float_to_rep(&f, &representation);

    /* Print first normal number*/
    printf("Normal representation: S: %d M: %s E: %d Type %d Val: %.50f \n", 
        representation.sign, 
        representation.mantissa, 
        representation.exponent,
         representation.type, f);

    return 0;
}
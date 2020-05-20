package source;

import java.util.ArrayList;

public class ThirdDegreePolynomial {
    private double coefficient0, coefficient1, coefficient2, coefficient3;

    public ThirdDegreePolynomial(double coefficient0, double coefficient1, double coefficient2, double coefficient3) {
        this.coefficient0 = coefficient0;
        this.coefficient1 = coefficient1;
        this.coefficient2 = coefficient2;
        this.coefficient3 = coefficient3;
    }

    public ThirdDegreePolynomial() {
        this.coefficient0 = 0;
        this.coefficient1 = 0;
        this.coefficient2 = 0;
        this.coefficient3 = 0;
    }

    /** @role : This function calculate result of "this" with "valueX".
     * @param valueX : unknown attribute, polynomial parameter.
     * @return double, result of polynomial.
     */
    public double calculated(double valueX) {
        return this.coefficient0 + valueX*(this.coefficient1 + valueX*(this.coefficient2 + valueX*this.coefficient3));
    }

    /**@role  : Calculate the result of the third derivative of "this" with parameter "valueX".
     * @param valueX : unknown attribute, polynomial parameter.
     * @return double, result of polynomial.
     */
    public double calculatedDerivative(double valueX){
        return this.coefficient1 + valueX*(2*this.coefficient2 + 3*valueX*this.coefficient3);
    }

    /** @role : Calculate the result of the second derivative of "this" with parameter "valueX".
     * @param valueX : unknown attribute, polynomial parameter.
     * @return double, result of polynomial.
     */
    public double calculatedDerivationTwo(double valueX) {
        return 2*this.coefficient2 + 6*valueX*this.coefficient3;
    }


}

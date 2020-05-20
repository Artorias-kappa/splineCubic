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

    public double calculated(double valueX) {
        return this.coefficient0 + valueX*(this.coefficient1 + valueX*(this.coefficient2 + valueX*this.coefficient3));
    }

    public double calculatedDerivative(double valueX){
        return this.coefficient1 + valueX*(this.coefficient2 + valueX*this.coefficient3);
    }


}

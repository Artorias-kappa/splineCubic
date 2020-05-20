package source;

import java.util.ArrayList;

public class vector {
    private int numberElement;
    private ArrayList<Double> tabElement;


    public vector(int numberElement, double tabElement[]) {
        this.numberElement = numberElement;
        this.tabElement = new ArrayList<Double>();
        this.initTab(tabElement);
    }

    public vector() {
        this.numberElement = 0;
        this.tabElement = new ArrayList<Double>();
    }

    public void initTab(double tabElement[]) {
        for (int i = 0 ; i < this.numberElement ; ++i) {
            this.tabElement.add(tabElement[i]);
        }
    }

    public void insert(int i, double value) {
        this.tabElement.remove(i);
        this.tabElement.add(i, value);
    }


}

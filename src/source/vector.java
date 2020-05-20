package source;

public class vector {
    private int numberElement;
    private float tabElement[];


    vector(int numberElement, float tabElement[]) {
        this.numberElement = numberElement;
        this.tabElement = new float[numberElement];
    }

    vector(int numberElement) {
        this.numberElement = numberElement;
        this.tabElement = new float[numberElement];
    }

    public void initTab(float tabElement[]) {
        for (int i = 0 ; i < this.numberElement ; ++i) {
            this.tabElement[i] = tabElement[i];
        }
    }


}

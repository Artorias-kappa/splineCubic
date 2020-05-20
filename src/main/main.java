package main;

import java.util.ArrayList;

public class main {




	public static void main(String[] args) {
		
		int sizeTest = 4;
		
		ArrayList<Double> test = initTab(sizeTest);

		System.out.println(display(test, sizeTest));





	}

	public static ArrayList<Double> initTab(int size) {
		ArrayList<Double> newList = new ArrayList<Double>();

		for (int i = 0 ; i < size ; ++i) {
			for (int j = 0 ; j < size ; ++j) {
				if (i == j) {
					newList.add(i * size + j, 4.0);
				} else if (i*i +1 == j) {
					newList.add(i * size + j, 1.0);
				} else if (i*i - 1 == j) {
					newList.add(i * size + j, 1.0);
				} else {
					newList.add(i * size + j, 0.0);
				}
			}
		}
		return newList;
	}

	public static String display(ArrayList<Double> list, int size) {

		String display = "";

		for (int i = 0 ; i < list.size() ; ++i) {
			for (int j = 0 ; j < list.size() ; ++j) {
				display += list.get(i * 4 + j);
			}
		}
		return display;
	}



}




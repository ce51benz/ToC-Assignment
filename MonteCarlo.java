import java.math.BigDecimal;
import java.math.MathContext;
import java.util.Random;
import java.util.Scanner;

import javax.swing.text.html.HTMLDocument.HTMLReader.IsindexAction;


public class MonteCarlo {
	public static final BigDecimal FOUR = new BigDecimal(4);
	public static double calFunction(double x,double y){
		return Math.pow(x,2) + Math.pow(y, 2);
	}
	
	public static boolean isAllDigit(String str){
		for(int k = 0;k < str.length();k++){
			if(!((str.charAt(k) >= 0x30) && (str.charAt(k)<=0x39)))
				return false;
		}
		return true;
	}
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		MathContext precision = new MathContext(1000);
		double x,y;
		String input;
		long k;
		Random generator = new Random(System.currentTimeMillis());
		BigDecimal totalSample = BigDecimal.ZERO,rightSample = BigDecimal.ZERO;
		System.out.println("KMITL TOC1/2557 Assignment 3-1 Monte Carlo method");
		System.out.println("[Member]");
		System.out.println("1.Maturose Kappako\t55010977");
		System.out.println("2.Suratchanan Kraidech\t55011362");
		System.out.println();
		
		//Receive input from user
		while(true){
		System.out.print("Enter total of sample that you want:");
		input = sc.nextLine();
		if(!isAllDigit(input))
			System.out.println("Input invalid please try again.");
		else{
			k = Long.parseLong(input);
			break;
			}
		}
		int i =0;
		
		//Loop to do Monte Carlo algorithm.
		while(i < k){
		//Random x and y in range of 0 to 1
		x = generator.nextDouble();
		y = generator.nextDouble();
		
		//If x^2 + y^2 <= 1 then count it as right sample
		if(calFunction(x, y) <= 1)
			rightSample = rightSample.add(BigDecimal.ONE);
		
		//count totalsample...
		totalSample = totalSample.add(BigDecimal.ONE);
		i++;
		}
		
		System.out.println("Total sample = "+totalSample);
		System.out.println("Right sample = "+rightSample);
		
		//Find ratio of sample and multiply by 4 to get result
		BigDecimal ratio = rightSample.divide(totalSample,precision).multiply(FOUR,precision);
		System.out.println("Ratio = "+ratio);
	}

}
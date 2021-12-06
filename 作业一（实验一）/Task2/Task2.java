import java.util.Scanner;
import java.lang.Math;;

public class Task2{ 
	public static void main(String[] args){
		int maxnum = 0;
		Scanner in=new Scanner(System.in);
		int num[] = new int[1000];
		String str[] = new String[1000];
		str = in.nextLine().split(" ");
		for(int i = 0; i < str.length; i++) {
			num[i] = Integer.parseInt(str[i]);
			maxnum = java.lang.Math.min(maxnum, num[i]);
		}
		int now = 0;
		for(int i = 0 ; i < str.length; i++)
		{
			now += num[i];
			maxnum = java.lang.Math.max(maxnum, now);
			if(now < 0) now = 0;
		}
		System.out.println(maxnum);
	}
}
package newlangl;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
public class Test1 {
		public static void main(String args[]){
				try{
				    File f = new File("test.txt");
				    BufferedReader br = new BufferedReader(new FileReader(f));

				    int c = br.read();
				    while(c!= -1){
					System.out.print((char)c);
					c=br.read();
				    }
				    br.close();
				}catch(IOException e){
				    System.out.println(e);
				}
		}
}
import java.net.*;
import java.io.*;

public class Client {

public static void main(String args[]) throws Exception {
  Socket c = new Socket("192.168.126.174", 1234);

  BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

  System.out.print("Introdu sirul: ");
  String sir = reader.readLine();
  System.out.print("Introdu caracterul: ");
  char ch = (char) reader.read();

  DataInputStream socketIn = new DataInputStream(c.getInputStream());
  DataOutputStream socketOut = new DataOutputStream(c.getOutputStream());

  short len = (short) sir.length();
  socketOut.writeShort(len);
  socketOut.writeBytes(sir);
  socketOut.writeByte((byte) ch);
  socketOut.flush();

  int count = socketIn.readUnsignedShort();
  System.out.println("Caracterul " + ch + " apare de " + count + " ori, pe urmatoarele pozitii: ");
  for(int i = 0; i < count; i++)
  {
    int pos = socketIn.readUnsignedShort();
        System.out.print(pos + " ");
  }
  System.out.println();

  reader.close();
  socketIn.close();
  socketOut.close();
  c.close();
}

}

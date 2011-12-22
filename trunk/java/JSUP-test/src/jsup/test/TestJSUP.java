package jsup.test;

import br.com.jsup.hardware.JSUPHardwareManager;

public class TestJSUP {
	public static void main(String[] args) {
		long directorySize = JSUPHardwareManager.getInstance().getDirectorySize("/home/guilherme/Downloads");

		System.out.println(directorySize);
	}
}

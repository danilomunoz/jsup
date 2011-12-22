package br.com.jsup.hardware;


public class JSUPHardwareManager {
	
	/**
	 * Library names
	 * @author Guilherme Gotardo
	 *
	 */
	public enum LIBRARY_ARCH {
		JSUP_x86,
		JSUP_x64,
	}
	
	/**
	 * The instance of {@link JSUPHardwareManager}
	 */
	private static JSUPHardwareManager instance;
	
	/**
	 * Current library architecture
	 */
	private LIBRARY_ARCH library = LIBRARY_ARCH.JSUP_x64;

	/**
	 * Load JSUP native library
	 */
	static {
		try {
			instance = new JSUPHardwareManager();
			System.loadLibrary(instance.getCurrentLibraryArchitecture().name());
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * Default constructor
	 * @throws Exception
	 */
	public JSUPHardwareManager() throws Exception {
		loadPlataform();
		loadSystemArchitecture();
	}
	
	/**
	 * Load the system architecture
	 */
	private void loadSystemArchitecture() {
		String osType= System.getProperty("os.arch");
		
		if (!osType.contains("64")) {
			library = LIBRARY_ARCH.JSUP_x86;
		}
	}

	/**
	 * Singleton method
	 * @return A instance of {@link JSUPHardwareManager}
	 */
	public static JSUPHardwareManager getInstance() {
		return instance;
	}

	/**
	 * Get the current library architecture
	 * @return A enum value
	 */
	public LIBRARY_ARCH getCurrentLibraryArchitecture() {
		return this.library;
	}
	
	/**
	 * Get running OS
	 * @throws Exception 
	 */
	private void loadPlataform() throws Exception {
		String osName = System.getProperty("os.name").toLowerCase();

		if (osName.indexOf("linux") < 0) {
			throw new Exception("OS Not suported, please use Unix distribuition.");
		}
	}

	/**
	 * Get the free space in bytes from partition
	 * @param partitionName The name of partition
	 * @return Free bytes of partition
	 */
	public native long getPartitionFreeSize(String partitionName);

	/**
	 * Get total space in bytes from partition
	 * @param partitionName The name of partition
	 * @return Total bytes of partition
	 */
	public native long getPartitionTotalSize(String partitionName);

	/**
	 * Get used space in bytes from partition
	 * @param partitionName The name of the partition 
	 * @return Total used bytes of partition
	 */
	public native long getPartitionUsedSize(String partitionName);
	/**
	 * Get the serial of a device
	 * @param deviceName The device that you want know the serial
	 * @return The serial number of the device
	 */
	public native String getHardDiskSerial(String deviceName);

	/**
	 * Get the model of a device
	 * @param deviceName The device that you want know the model
	 * @return The model of the device
	 */
	public native String getHardDiskModel(String deviceName);

	/**
	 * Get size of a directory
	 * @param directory The path of directory
	 * @return Total size of the directory
	 */
	public native long getDirectorySize(String directory);
}

package br.com.jsup.hardware;

import static org.junit.Assert.fail;

import org.junit.Test;

public class JSUPHardwareManagerTest {

	@Test
	public void testGetCurrentLibraryArchitecture() {
		JSUPHardwareManager.getInstance().getCurrentLibraryArchitecture();
	}

	@Test
	public void testGetPartitionFreeSpace() {
		long partitionFreeSpace = JSUPHardwareManager.getInstance().getPartitionFreeSize("/");
		if (partitionFreeSpace <= 0) {
			fail("Cannot get free space");
		}
	}

	@Test
	public void testGetPartitionTotalSpace() {
		long partitionFreeSpace = JSUPHardwareManager.getInstance().getPartitionTotalSize("/");
		if (partitionFreeSpace <= 0) {
			fail("Cannot get total space");
		}
	}

	@Test
	public void testGetPartitionUsedSpace() {
		long partitionFreeSpace = JSUPHardwareManager.getInstance().getPartitionUsedSize("/");
		if (partitionFreeSpace <= 0) {
			fail("Cannot get used space");
		}
	}

	@Test
	public void testGetHardDiskSerial() {
		String partitionFreeSpace = JSUPHardwareManager.getInstance().getHardDiskSerial("/");
		if (!partitionFreeSpace.isEmpty()) {
			fail("Cannot get hd serial number");
		}
	}

	@Test
	public void testGetHardDiskModel() {
		String partitionFreeSpace = JSUPHardwareManager.getInstance().getHardDiskModel("/dev/sda5");
		if (partitionFreeSpace.isEmpty()) {
			fail("Cannot get hd model");
		}
	}

	@Test
	public void testGetDirectorySize() {
		long partitionFreeSpace = JSUPHardwareManager.getInstance().getDirectorySize("/home/guilherme/Downloads");
		if (partitionFreeSpace <= 0) {
			fail("Cannot get directory size");
		}
	}

}

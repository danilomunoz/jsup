/*
 * JSUPHardwareManager.cpp
 *
 *  Created on: Dec 20, 2011
 *      Author: root
 */
#include "br_com_jsup_hardware_JSUPHardwareManager.h"

#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <sys/statvfs.h>
#include <sys/statfs.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/hdreg.h>
#include <errno.h>
#include <dirent.h>
#include <stdio.h>


using namespace std;

unsigned char isFile 	= 		0x8;
unsigned char isFolder 	=		0x4;


const char * getStringUTF(JNIEnv *env, jstring convertString) {
	jboolean *cp = new jboolean;
	const char *str = env->GetStringUTFChars(convertString, cp);

	free(cp);

	return str;
}

void releaseStringUTF(JNIEnv *env, jstring path, const char *str) {
	env->ReleaseStringUTFChars(path, str);
}

int getDiskInformations(JNIEnv *env, jstring path, struct statvfs* fiData) {
	const char *str = getStringUTF(env, path);

	int status = statvfs(str, fiData);

	releaseStringUTF(env, path, str);

	return status;
}

string convertCharsToString(unsigned char * ch) {
	string serial(reinterpret_cast< char const* >(ch));
	return serial;
}

JNIEXPORT jlong JNICALL Java_br_com_jsup_hardware_JSUPHardwareManager_getPartitionFreeSize(JNIEnv *env, jobject, jstring path) {
	jlong ret = 0;
	struct statvfs * fiData = new struct statvfs;

	int status = getDiskInformations(env, path, fiData);

	if (status == 0) {
		long long avail = fiData->f_bavail;
		avail *= fiData->f_bsize;

		ret =  avail;
	}

	free(fiData);

	return ret;
}

JNIEXPORT jlong JNICALL Java_br_com_jsup_hardware_JSUPHardwareManager_getPartitionTotalSize(JNIEnv *env, jobject, jstring path) {
	jlong ret = 0;
	struct statvfs * fiData = new struct statvfs;

	int status = getDiskInformations(env, path, fiData);

	if (status == 0) {
		long long total = fiData->f_blocks;
		total *= fiData->f_bsize;

		ret = total;
	}

	free(fiData);

	return ret;
}

JNIEXPORT jlong JNICALL Java_br_com_jsup_hardware_JSUPHardwareManager_getPartitionUsedSize(JNIEnv *env, jobject, jstring path) {
	jlong ret = 0;
	struct statvfs * fiData = new struct statvfs;

	int status = getDiskInformations(env, path, fiData);

	if (status == 0) {
		long long used = (fiData->f_blocks - fiData->f_bavail);
		used *= fiData->f_bsize;

		ret = used;
	}

	free(fiData);

	return ret;
}

/**
 * Get all hard disk informations
 */
int loadHDInformation(struct hd_driveid hd, const char *str) {
	int fd = 0;
	int ret = -1;

	if ((fd = open(str, O_RDONLY|O_NONBLOCK)) >= 0) {
		ret = ioctl(fd, HDIO_GET_IDENTITY, &hd);
	}

	return ret;
}

/**
 * Get hard disk serial number
 */
JNIEXPORT jstring JNICALL Java_br_com_jsup_hardware_JSUPHardwareManager_getHardDiskSerial(JNIEnv *env, jobject, jstring device) {
	jstring ret = env->NewStringUTF("");

	int fd;
	const char *str = getStringUTF(env, device);
	static struct hd_driveid hd;

	if ((fd = open(str, O_RDONLY|O_NONBLOCK)) >= 0) {
		if (!ioctl(fd, HDIO_GET_IDENTITY, &hd)) {
			string serial = convertCharsToString(hd.serial_no);
			ret = env->NewStringUTF(serial.c_str());
		}
	}

	releaseStringUTF(env, device, str);

	return ret;
}

JNIEXPORT jstring JNICALL Java_br_com_jsup_hardware_JSUPHardwareManager_getHardDiskModel(JNIEnv *env, jobject, jstring device) {
	jstring ret = env->NewStringUTF("");

	int fd;
	const char *str = getStringUTF(env, device);
	static struct hd_driveid hd;

	if ((fd = open(str, O_RDONLY|O_NONBLOCK)) >= 0) {
		if (!ioctl(fd, HDIO_GET_IDENTITY, &hd)) {
			string serial = convertCharsToString(hd.model);
			ret = env->NewStringUTF(serial.c_str());
		}
	}

	releaseStringUTF(env, device, str);

	return ret;
}

long getDirectorySize(string path) {
	long total = 0;

	DIR * pdir = opendir(path.c_str());

	if (pdir) {
		struct dirent *pent;

		while ((pent=readdir(pdir))) {
			string name = pent->d_name;

			if (name.compare(".") == 0 || name.compare("..") == 0) {
				continue;
			}

			string absolutePath;
			absolutePath.append(path);
			absolutePath.append("/");
			absolutePath.append(name);

			if (pent->d_type == isFolder) {
				total += getDirectorySize(absolutePath);
			} else {
				FILE * pFile;

				pFile = fopen(absolutePath.c_str(),"rb");

				if (pFile != NULL) {
					fseek (pFile, 0, SEEK_END);
					total += ftell(pFile);
					fclose (pFile);
				}
			}
		}

		closedir(pdir);
	}

	return total;
}

JNIEXPORT jlong JNICALL Java_br_com_jsup_hardware_JSUPHardwareManager_getDirectorySize(JNIEnv * env, jobject, jstring directory) {
	const char *str = getStringUTF(env, directory);

	jlong ret = getDirectorySize(str);

	return ret;
}



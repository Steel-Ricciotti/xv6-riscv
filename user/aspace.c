#include "kernel/types.h"
#include "user/user.h"

// 
// Write a C program to be executed in Unix environment. It takes three command line arguments
// with the following information:
// • The type of the page table. Only two values 1 and 2 can be accepted. 1 means single-level
// linear page table and 2 means two-level tree-structured page table.
// • The total number of bits in the binary format of the memory address. This can be an integer
// in the range [8..63].
// • The page size in terms of the number of KB (1024 Bytes). This can be 1, 2, 4, 8, 16, 32,
// 64, 128, 256, 512.
// If the given three arguments are not consistent with each other, your program will terminate with
// an error message. The error message should include an explanation why the arguments cannot be
// accepted. For example, (1, 10, 2) cannot be accepted because with 10-bit address, the memory size
// is 1 KB, so it is impossible to have a page of size 2 KB.
// If the given three arguments are consistent, your program should give the following output (in
// decimal):
// • the size of the memory in terms of the number of bytes, the number of KB, the number of
// MB, or the number of GB, whichever is the most appropriate.
// • the total number of pages
// • the total number of page table entries
// • the size of the page table in terms of the number of bytes
// • the total number of bits in an address for the VPN
// • the total number of bits in an address for the offset within a page
// • the total number of page table entries in a page of a page table (type 2 only)
// • the total number of pages in a page table (type 2 only)
// • the total number of bits in an address for the page directory index (type 2 only)
// • the total number of bits in an address for the page table index (type 2 only)
// After the output of the above data, your program should repeatedly prompt the user to input a
// decimal virtual address and output the related information (including any error messages).
// If the input address is not consistent with the command line arguments, your program should print
// an error message and prompt the user for the next input of the virtual address. The error message
// should include an explanation why the input cannot be accepted. For example, with 10-bit address,
// an input of virtual address 12345 cannot be accepted because the memory size is only 1 KB.
// If the input address is consistent with the command line arguments, your program should provide
// the following output:
// • the VPN of the input address in decimal format
// • the page offset of the input address in decimal format
// • the page directory index of the input address in decimal format (type 2 only)
// • the page table index of the input address in decimal format (type 2 only)
// • the input address in binary format
// • the VPN of the input address in binary format
// • the page offset of the input address in binary format
// • the page directory index of the input address in binary format (type 2 only)
// • the page table index of the input address in binary format (type 2 only)
// Note that the numbers in binary format should include zeros at the beginning if necessary. After
// the above output, the program should prompt the user for the next input of the virtual addres
int main(int argc, char *argv[]) {
    int type = atoi(argv[1]);
    if (type != 1 && type != 2) {
        printf("Error: Type must be 1 or 2, got %d\n", type);
        exit(1);
    }
    int address_bits = atoi(argv[2]);
    printf("Test1");
    if (address_bits < 8 || address_bits > 63) {
        printf("Error: Address bits must be in [8..63], got %d\n", address_bits);
        exit(1);
    }    
    int page_size = atoi(argv[3]);
    int valid_sizes[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
    int valid_size = 0;
    for (int i = 0; i < 10; i++) {
            if (page_size == valid_sizes[i]) valid_size = 1;
        }    
    if (valid_size == 0) {
        printf("Error: Page size must be one of {1,2,4,8,16,32,64,128,256,512}, got %d\n", page_size);
        exit(1);
    }
    printf("Test2\n");

    uint64 memory_size = 1ULL << address_bits; 
    // printf("Memory size: %d bytes\n", memory_size);
    printf("Address bits: %d\n", address_bits);
    int memory_size_gb = memory_size / (1ULL << 30);
    printf("Memory size in GB: %d\n", memory_size_gb);
    int page_size_bytes = page_size * 1024;
    if (memory_size < page_size_bytes) {
        printf("Inconsistent arguments");
        exit(1);
    }
    printf("Test3\n");
    int total_pages = memory_size / page_size_bytes;
    int total_entries = total_pages; //Total entries for type 1
    int page_table_size = total_entries * sizeof(int);
    int vpn_bits = address_bits - (page_size < 1024 ? 10 : 11);
    int offset_bits = address_bits - vpn_bits;
    int entries_per_page = (type == 2) ? (1 << (vpn_bits - 10)) : 0;
    int total_pages_in_table = (type == 2) ? (1 << (vpn_bits - 10)) : 0;
    int dir_index_bits = (type == 2) ? (vpn_bits - 10) : 0;
    int table_index_bits = (type == 2) ? 10 : 0;
    printf("Memory size: %d bytes (%d KB, %d MB, %d GB)\n", memory_size_gb, memory_size_gb / 1024, memory_size_gb / (1024 * 1024), memory_size_gb / (1024 * 1024 * 1024));
    printf("Total pages: %d\n", total_pages);
    printf("Total page table entries: %d\n", total_entries);
    printf("Size of page table: %d bytes\n", page_table_size);
    printf("Bits for VPN: %d\n", vpn_bits);
    printf("Bits for offset: %d\n", offset_bits);
    if (type == 2) {
        printf("Entries per page in page table: %d\n", entries_per_page);
        printf("Total pages in page table: %d\n", total_pages_in_table);
        printf("Bits for page directory index: %d\n", dir_index_bits);
        printf("Bits for page table index: %d\n", table_index_bits);
    }
    // while (1) {
    //     fprintf(1, "Enter virtual address: ");
    //     int addr = atoi(gets(0, 10));
    //     if (addr < 0 || addr >= memory_size) {
    //         fprintf(2, "Invalid address: %d is out of range [0, %d)\n", addr, memory_size);
    //         continue;
    //     }
    //     int vpn = addr >> offset_bits;
    //     int offset = addr & ((1 << offset_bits) - 1);
    //     int dir_index = (type == 2) ? (vpn >> 10) : 0;
    //     int table_index = (type == 2) ? (vpn & ((1 << 10) - 1)) : vpn;
    //     printf("VPN: %d\n", vpn);
    //     printf("Offset: %d\n", offset);
    //     if (type == 2) {
    //         printf("Page Directory Index: %d\n", dir_index);
    //         printf("Page Table Index: %d\n", table_index);
    //     }
    //     printf("Address in binary: ");
    //     for (int i = bits - 1; i >= 0; i--) {
    //         printf("%d", (addr >> i) & 1);
    //     }
    //     printf("\nVPN in binary: ");
    //     for (int i = vpn_bits - 1; i >= 0; i--) {
    //         printf("%d", (vpn >> i) & 1);
    //     }
    //     printf("\nOffset in binary: ");
    //     for (int i = offset_bits - 1; i >= 0; i--) {
    //         printf("%d", (offset >> i) & 1);
    //     }
    //     if (type == 2) {
    //         printf("\nPage Directory Index in binary: ");
    //         for (int i = dir_index_bits - 1; i >= 0; i--) {
    //             printf("%d", (dir_index >> i) & 1);
    //         }
    //         printf("\nPage Table Index in binary: ");
    //         for (int i = table_index_bits - 1; i >= 0; i--) {
    //             printf("%d", (table_index >> i) & 1);
    //         }
    //     }
    //     printf("\n");
    // }

    exit(0);
}
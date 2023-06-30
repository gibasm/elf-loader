#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef uint32_t Elf32_Addr;
typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Off;
typedef uint32_t Elf32_Sword;
typedef uint32_t Elf32_Word;

#define EI_NIDENT   16
#define EI_VERSION  6

/* [0x7F, 'E', 'L', 'F'] */
#define ELF_MAGIC   0x464c457fU

typedef struct 
__attribute__((aligned, __packed__))
{
    unsigned char e_ident[EI_NIDENT];
    Elf32_Half e_type;
    Elf32_Half e_machine;
    Elf32_Word e_version;
    Elf32_Addr e_entry;
    Elf32_Off e_phoff;
    Elf32_Off e_shoff;
    Elf32_Word e_flags;
    Elf32_Half e_ehsize;
    Elf32_Half e_phentsize;
    Elf32_Half e_phnum;
    Elf32_Half e_shentsize;
    Elf32_Half e_shnum;
    Elf32_Half e_shstrndx;
} Elf32_Ehdr;

Elf32_Ehdr read_elf32_header(FILE* f);

int main(int argc, char** argv) 
{
    if (argc != 2)
    {
        puts("Usage: ./myld <elf>");
        return 1;
    }
 
    FILE* f = fopen((const char*) argv[1], "rb");

    if(f == NULL)
    {
        printf("Error: File %s cannot be opened!\n", argv[1]);
        return 1;
    }

    Elf32_Ehdr ehdr = read_elf32_header(f);

    fclose(f);
    return 0;
}

Elf32_Ehdr read_elf32_header(FILE* f)
{
    Elf32_Ehdr ehdr;
    fread(&ehdr, 1, sizeof(Elf32_Ehdr), f);
    /* check the ELF magic number */
    uint32_t magicn;
    memcpy(&magicn, ehdr.e_ident, 4);

    if(magicn != ELF_MAGIC)
    {
        puts("Error: Not an ELF file!");
        fclose(f);
        exit(2);
    }
     
    return ehdr;
}

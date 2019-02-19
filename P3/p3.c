#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <elf.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Para almacenar la informacion de las cabeceras de secciones
Elf32_Shdr *shInfoTable;

// Para almacenar la informacion de las cabeceras de programa
Elf32_Phdr *phInfoTable;

// Para almacenar los nombres de las secciones
char *sh_stringTable;

// Para almacenar la cabecera del fichero ELF
Elf32_Ehdr ehdr;

// Devuelve la clase del fichero
char *getClass () {
  
	static char aux[32];

  	switch (ehdr.e_ident[EI_CLASS]) {
    		case ELFCLASSNONE: return "Invalid class";
    		case ELFCLASS32:   return "ELF32 (32-bit objects)";
    		case ELFCLASS64:   return "ELF64 (64-bit objects)";
    		default:
      			sprintf(aux, "Unknown: %x", ehdr.e_ident[EI_CLASS]);
      			return aux;
    	}

}

// Devuelve la codificacion de los datos del fichero
char *getDataEncoding () {
  
	static char aux[32];

  	switch (ehdr.e_ident[EI_DATA])	{
    		case ELFDATANONE: return "Invalid data encoding";
    		case ELFDATA2LSB: return "2's complement, little endian";
    		case ELFDATA2MSB: return "2's complement, big endian";
    		default:
      			sprintf(aux, "Unknown: %x", ehdr.e_ident[EI_DATA]);
      			return aux;
    	}

}

// Devuelve el sistema operativo para el que se ha compilado el fichero
char *getOSABI() {

    static char aux[32];

    switch (ehdr.e_ident[EI_OSABI]) {
    	case ELFOSABI_SYSV: return "UNIX System V ABI";
    	case ELFOSABI_HPUX: return "HP-UX";
    	case ELFOSABI_NETBSD: return "NetBSD";
    	case ELFOSABI_LINUX: return "Linux";
    	case ELFOSABI_SOLARIS: return "Sun Solaris";
    	case ELFOSABI_AIX: return "IBM AIX";
    	case ELFOSABI_IRIX: return "SGI Irix";
    	case ELFOSABI_FREEBSD: return "FreeBSD";
    	case ELFOSABI_TRU64: return "Compaq TRU64 UNIX";
    	case ELFOSABI_MODESTO: return "Novell Modesto";
    	case ELFOSABI_OPENBSD: return "OpenBSD";
    	case ELFOSABI_ARM: return "ARM";
    	case ELFOSABI_STANDALONE: return "Standalone (embedded) application";
    	default:
      		sprintf(aux, "Unknown: %x", ehdr.e_ident[EI_OSABI]);
      		return aux;
    }

}

// Devuelve el tipo del archivo objeto
char *getType() {

    static char aux[32];

    switch (ehdr.e_type) {
    	case ET_NONE: return "NONE (None)";
    	case ET_REL:  return "REL (Relocatable file)";
    	case ET_EXEC: return "EXEC (Executable file)";
    	case ET_DYN:  return "DYN (Shared object file)";
    	case ET_CORE: return "CORE (Core file)";
	default:
        	if ((ehdr.e_type >= ET_LOOS) && (ehdr.e_type <= ET_HIOS)) 
			sprintf(aux, "OS Specific: (%x)", ehdr.e_type);
        	else if ((ehdr.e_type >= ET_LOPROC) && (ehdr.e_type <= ET_HIPROC)) 
			sprintf (aux, "Processor Specific: (%x)", ehdr.e_type);
        	else sprintf(aux, "Unknown: %x", ehdr.e_type);
        	return aux;
    }

}

// Devuelve la arquitectura
char *getMachine() {

    static char aux[64];
    
    switch (ehdr.e_machine) {
    	case EM_NONE:        return "No machine";
    	case EM_M32:         return "AT&T WE 32100";
    	case EM_SPARC:       return "SUN SPARC";
    	case EM_386:         return "Intel 80386";
    	case EM_68K:         return "Motorola m68k family";
    	case EM_88K:         return "Motorola m88k family";
    	case EM_860:         return "Intel 80860";
    	case EM_MIPS:        return "MIPS R3000 big-endian";
    	case EM_S370:        return "IBM System/370";
    	case EM_MIPS_RS3_LE: return "MIPS R4000 little-endian";
    	case EM_PARISC:      return "HPPA";
    	case EM_VPP500:      return "Fujitsu VPP500";
    	case EM_SPARC32PLUS: return "Sun's \"v8plus\"";
    	case EM_960:         return "Intel 80960";
    	case EM_PPC:         return "PowerPC";
    	case EM_PPC64:       return "PowerPC 64-bit";
    	case EM_S390:        return "IBM S390";
    	case EM_V800:        return "NEC V800 series";
    	case EM_FR20:        return "Fujitsu FR20";
    	case EM_RH32:        return "TRW RH-32";
    	case EM_RCE:         return "Motorola RCE";
    	case EM_ARM:         return "ARM";
    	case EM_FAKE_ALPHA:  return "Digital Alpha";
    	case EM_SH:          return "Hitachi SH";
    	case EM_SPARCV9:     return "SPARC v9 64-bit";
    	case EM_TRICORE:     return "Siemens Tricore";
    	case EM_ARC:         return "Argonaut RISC Core";
    	case EM_H8_300:      return "Hitachi H8/300";
    	case EM_H8_300H:     return "Hitachi H8/300H";
    	case EM_H8S:         return "Hitachi H8S";
    	case EM_H8_500:      return "Hitachi H8/500";
    	case EM_IA_64:       return "Intel Merced";
    	case EM_MIPS_X:      return "Stanford MIPS-X";
    	case EM_COLDFIRE:    return "Motorola Coldfire";
    	case EM_68HC12:      return "Motorola M68HC12";
    	case EM_MMA:         return "Fujitsu MMA Multimedia Accelerator";
    	case EM_PCP:         return "Siemens PCP";
    	case EM_NCPU:        return "Sony nCPU embeeded RISC";
    	case EM_NDR1:        return "Denso NDR1 microprocessor";
    	case EM_STARCORE:    return "Motorola Start*Core processor";
    	case EM_ME16:        return "Toyota ME16 processor";
    	case EM_ST100:       return "STMicroelectronic ST100 processor";
    	case EM_TINYJ:       return "Advanced Logic Corp. Tinyj emb.fam";
    	case EM_X86_64:      return "AMD x86-64 architecture";
    	case EM_PDSP:        return "Sony DSP Processor";
    	case EM_FX66:        return "Siemens FX66 microcontroller";
    	case EM_ST9PLUS:     return "STMicroelectronics ST9+ 8/16 mc";
    	case EM_ST7:         return "STmicroelectronics ST7 8 bit mc";
    	case EM_68HC16:      return "Motorola MC68HC16 microcontroller";
    	case EM_68HC11:      return "Motorola MC68HC11 microcontroller";
    	case EM_68HC08:      return "Motorola MC68HC08 microcontroller";
    	case EM_68HC05:      return "Motorola MC68HC05 microcontroller";
    	case EM_SVX:         return "Silicon Graphics SVx";
    	case EM_VAX:         return "Digital VAX";
    	case EM_CRIS:        return "Axis Communications 32-bit embedded processor";
    	case EM_JAVELIN:     return "Infineon Technologies 32-bit embedded processor";
    	case EM_FIREPATH:    return "Element 14 64-bit DSP Processor";
    	case EM_ZSP:         return "LSI Logic 16-bit DSP Processor";
    	case EM_MMIX:        return "Donald Knuth's educational 64-bit processor";
    	case EM_HUANY:       return "Harvard University machine-independent";
    	case EM_PRISM:       return "SiTera Prism";
    	case EM_AVR:         return "Atmel AVR 8-bit microcontroller";
    	case EM_FR30:        return "Fujitsu FR30";
    	case EM_D10V:        return "Mitsubishi D10V";
    	case EM_D30V:        return "Mitsubishi D30V";
    	case EM_V850:        return "NEC v850";
    	case EM_M32R:        return "Mitsubishi M32R";
    	case EM_MN10300:     return "Matsushita MN10300";
    	case EM_MN10200:     return "Matsushita MN10200";
    	case EM_PJ:          return "picoJava";
    	case EM_OPENRISC:    return "OpenRISC 32-bit embedded processor";
    	case EM_ARC_A5:      return "ARC Cores Tangent-A5";
    	case EM_XTENSA:      return "Tensilica Xtensa Architecture";
    	default:
      		sprintf(aux, "Unknown: %x", ehdr.e_machine);
      		return aux;
    }

}

// Devuelve el nombre de la seccion
char *getSectionName(int i) {

	return (&sh_stringTable[i]);

}

// Devuelve el tipo de la seccion
char *getSectionType(Elf32_Word sh_type) {
  
	static char aux[32];

  	switch (sh_type) {
      		case SHT_NULL:            return "NULL";
      		case SHT_PROGBITS:        return "PROGBITS";
      		case SHT_SYMTAB:          return "SYMTAB";
      		case SHT_STRTAB:          return "STRTAB";
      		case SHT_RELA:            return "RELA";
      		case SHT_HASH:            return "HASH";
      		case SHT_DYNAMIC:         return "DYNAMIC";
      		case SHT_NOTE:            return "NOTE";
      		case SHT_NOBITS:          return "NOBITS";
      		case SHT_REL:             return "REL";
      		case SHT_SHLIB:           return "SHLIB";
      		case SHT_DYNSYM:          return "DYNSYM";
      		case SHT_INIT_ARRAY:      return "INIT_ARRAY";
      		case SHT_FINI_ARRAY:      return "FINI_ARRAY";
      		case SHT_PREINIT_ARRAY:   return "PREINIT_ARRAY";
      		case SHT_GNU_verdef:      return "VERDEF";
      		case SHT_GNU_verneed:     return "VERNEED";
      		case SHT_GNU_versym:      return "VERSYM";
      		case SHT_GROUP:           return "GROUP";
      		case SHT_SYMTAB_SHNDX:    return "SYMTAB_SHNDX";
      		case SHT_NUM:             return "NUM";
      		case SHT_GNU_LIBLIST:     return "GNU_LIBLIST";
      		case SHT_CHECKSUM:        return "CHECKSUM";
		default:
          		if ((sh_type >= SHT_LOPROC) && (sh_type <= SHT_HIPROC))
          			return "PROC-SPECIFIC";
          		else if ((sh_type >= SHT_LOOS) && (sh_type <= SHT_HIOS))
              			return "OS-SPECIFIC";
          		else if ((sh_type >= SHT_LOUSER) && (sh_type <= SHT_HIUSER))
              			return "APP-SPECIFIC";
          		else sprintf(aux,"Unknown: %x", sh_type);
          		return aux;
    }

}

// Deuelve los flags de la seccion
char *getSectionFlags(Elf32_Word sh_flags) {
    
	static char aux[32];

    	aux[0] = '\0';
	if (sh_flags & SHF_WRITE)            strcat(aux,"W");
    	if (sh_flags & SHF_ALLOC)            strcat(aux,"A");
    	if (sh_flags & SHF_EXECINSTR)        strcat(aux,"X");
    	if (sh_flags & SHF_MERGE)            strcat(aux,"M");
    	if (sh_flags & SHF_STRINGS)          strcat(aux,"S");
    	if (sh_flags & SHF_INFO_LINK)        strcat(aux,"I");
    	if (sh_flags & SHF_LINK_ORDER)       strcat(aux,"L");
    	if (sh_flags & SHF_OS_NONCONFORMING) strcat(aux,"O");
    	if (sh_flags & SHF_GROUP)            strcat(aux,"G");
    	if (sh_flags & SHF_TLS)              strcat(aux,"T");
    	if (sh_flags & SHF_MASKOS)           strcat(aux,"o");
    	if (sh_flags & SHF_MASKPROC)         strcat(aux,"p");
	if ((sh_flags) &&
    		!((SHF_WRITE | SHF_ALLOC | SHF_EXECINSTR | SHF_MERGE | SHF_STRINGS
           	| SHF_INFO_LINK | SHF_LINK_ORDER | SHF_OS_NONCONFORMING | SHF_GROUP
           	| SHF_TLS | SHF_MASKOS | SHF_MASKPROC) & sh_flags))
        	return "x"; 
	return aux;

}

// Devuelve el tipo del programa
char *getProgramType (Elf32_Word ph_type) {
    
	static char aux[32];

    	switch (ph_type) {
        	case PT_NULL:       return "NULL";
        	case PT_LOAD:       return "LOAD";
        	case PT_DYNAMIC:    return "DYNAMIC";
        	case PT_INTERP:     return "INTERP";
        	case PT_NOTE:       return "NOTE";
        	case PT_SHLIB:      return "SHLIB";
        	case PT_PHDR:       return "PHDR";
        	case PT_TLS:        return "TLS";
        	case PT_NUM:        return "NUM";
    		default:
        		if ((ph_type >= PT_LOPROC) && (ph_type <= PT_HIPROC))
            			return "PROC-SPECIFIC";
        		else if ((ph_type >= PT_LOOS) && (ph_type <= PT_HIOS))
            			return "OS-SPECIFIC";
        		else sprintf(aux,"Unknown: %x", ph_type);
        		return aux;
  }

}

// Devuelve los flags del programa
char *getProgramFlags (Elf32_Word ph_flags) {
    
	static char aux[6];
	int i;

	for (i = 0; i < 6; i++) aux[i] ='\0';

        if (ph_flags & PF_R)  aux[0] = 'R';
		else aux[0]= ' ';
    	if (ph_flags & PF_W)  aux[1] = 'W';
		else aux[1]= ' ';
    	if (ph_flags & PF_X)  aux[2] = 'E';
		else aux[2]= ' ';
    	if (ph_flags & PF_MASKOS)  aux[3] = 'O';
		else aux[3]= ' ';
    	if (ph_flags & PF_MASKPROC)  aux[4] = 'P';
	return aux;

}

int main(int argc, char *argv[]) {

	int fd;
	int i;
	int j;
	int offset;
	int max_offset;
	int seccion;
	int programa;
    	Elf32_Shdr shdr;
	Elf32_Phdr phdr;
        
    	// Se abre el fichero
    	if ((fd = open(argv[1], O_RDONLY)) == -1) printf("Error al abrir el fichero %s\n", argv[1]);

    	// Se lee la cabecera del fichero ELF
    	if (read(fd, &ehdr, sizeof(Elf32_Ehdr)) == -1)	{
		printf("Error al leer la cabecera del fichero %s\n", argv[1]);
	      	close(fd);
        	exit(1);
    	}

	// Se comprueba que el fichero sea de tipo ELF
    	if (ehdr.e_ident [EI_MAG0] != ELFMAG0 || ehdr.e_ident [EI_MAG1] != ELFMAG1
      	   || ehdr.e_ident [EI_MAG2] != ELFMAG2 || ehdr.e_ident [EI_MAG3] != ELFMAG3) {
        	printf("El fichero %s no es de tipo ELF\n", argv[1]);
        	close(fd);
        	exit(1);
   	}

	// Se imprime la cabecera del fichero ELF
        printf("ELF header:\n");
    	printf("  Magic:     ");
    	for (i=0; i < EI_NIDENT; i++) printf(" %02x", ehdr.e_ident[i]);
    	printf("\n");
    	printf("  Class:                             %s\n", getClass());
    	printf("  Data:                              %s\n", getDataEncoding());
    	printf("  Version:                           %d\n", ehdr.e_ident[EI_VERSION]);
    	printf("  OS/ABI:                            %s\n", getOSABI());
    	printf("  ABI Version:                       %d\n", ehdr.e_ident[EI_ABIVERSION]);
    	printf("  Type:                              %s\n", getType());
    	printf("  Machine:                           %s\n", getMachine());
    	printf("  Version:                           0x%x\n", ehdr.e_version);
    	printf("  Entry point address:               0x%x\n", ehdr.e_entry);
    	printf("  Start of program headers:          %d (bytes into file)\n", ehdr.e_phoff);
    	printf("  Start of section headers:          %d (bytes into file)\n", ehdr.e_shoff);
    	printf("  Flags:                             0x%x\n", ehdr.e_flags);
    	printf("  Size of this header:               %d (bytes)\n", ehdr.e_ehsize);
    	printf("  Size of program headers:           %d (bytes)\n", ehdr.e_phentsize);
    	printf("  Number of program headers:         %d\n", ehdr.e_phnum);
    	printf("  Size of section headers:           %d (bytes)\n", ehdr.e_shentsize);
    	printf("  Number of section headers:         %d\n", ehdr.e_shnum);
    	printf("  Section header string table index: %d\n", ehdr.e_shstrndx);

	// Se lee la tabla de strings con los nombres de seccion
    	// El offset es el resultado de sumar donde empiezan las cabeceras de seccion
    	// y el producto de numero de seccion de la tabla de strings por el tamanho de cabecera de seccion
    	offset = ehdr.e_shoff + ehdr.e_shstrndx * ehdr.e_shentsize;
	
	// Se posiciona en ese offset
    	lseek(fd, offset, SEEK_SET);

    	// Se almacena la seccion con la tabla de strings
    	if (read(fd, &shdr, sizeof(Elf32_Shdr)) == -1) {
        	printf("Error al leer la tabla de strings del fichero %s\n", argv[1]);
        	close(fd);
        	exit(1);
    	}

    	// Se posiciona en el comienzo de la seccion con la tabla de strings
    	lseek(fd, shdr.sh_offset, SEEK_SET);

    	sh_stringTable = (char *) malloc(sizeof(char)*shdr.sh_size);

    	// Se lee la tabla de strings
    	read(fd,sh_stringTable, shdr.sh_size);

	// Se lee la informacion de las cabeceras de seccion    	
	// El offset inicial es donde empiezan las cabeceras de seccion
    	offset = ehdr.e_shoff;
	
	// El offset maximo sera el offset inicial mas el producto del
	// numero de cabeceras de seccion por su tamanho
    	max_offset = offset + ehdr.e_shnum * ehdr.e_shentsize;

        shInfoTable = (Elf32_Shdr *)malloc(sizeof(Elf32_Shdr)*ehdr.e_shnum);

    	seccion = 0;
    	for (i = offset; i < max_offset; i += ehdr.e_shentsize) {
		// Se posiciona en el offset de la seccion
        	lseek(fd, i, SEEK_SET);

        	// Se leen los datos de la seccion
        	if (read(fd, &shdr, sizeof(Elf32_Shdr)) == -1) {
            		printf("Error al leer las secciones del fichero %s\n", argv[1]);
            		close(fd);
            		exit(1);
        	}

        	// Se almacenan los datos de la seccion
        	shInfoTable[seccion].sh_name = shdr.sh_name;
        	shInfoTable[seccion].sh_type = shdr.sh_type;
        	shInfoTable[seccion].sh_flags = shdr.sh_flags;
        	shInfoTable[seccion].sh_addr = shdr.sh_addr;
        	shInfoTable[seccion].sh_offset = shdr.sh_offset;
        	shInfoTable[seccion].sh_size = shdr.sh_size;
        	shInfoTable[seccion].sh_link = shdr.sh_link;
        	shInfoTable[seccion].sh_info = shdr.sh_info;
        	shInfoTable[seccion].sh_addralign = shdr.sh_addralign;
        	shInfoTable[seccion].sh_entsize = shdr.sh_entsize;
	
        	seccion++;
    	}

	// Se imprimen las cabeceras de seccion
	printf("\nSection Headers:\n");
    	printf("  [Nr] %-17s %-15s %-8s %-6s %-6s %-2s %-3s %-2s %-3s %-2s\n",           			"Name","Type","Addr","Off","Size","ES","Flg","Lk","Inf","Al");
    	for (i = 0; i < ehdr.e_shnum; i++) {
        	printf("  [%2d] %-17s %-15s %08x %06x %06x %02x %3s %2d %3x %2d\n",
			i, getSectionName(shInfoTable[i].sh_name) ,getSectionType(shInfoTable[i].sh_type), 
			shInfoTable[i].sh_addr,shInfoTable[i].sh_offset, shInfoTable[i].sh_size, 
			shInfoTable[i].sh_entsize, getSectionFlags(shInfoTable[i].sh_flags), 
			shInfoTable[i].sh_link,shInfoTable[i].sh_info, shInfoTable[i].sh_addralign);
    	}
    	printf("Key to Flags:\n");
    	printf("  W (write), A (alloc), X (execute), M (merge), S (strings)\n");
    	printf("  I (info), L (link order), G (group), x (unknown)\n");
    	printf("  O (extra OS processing required), o (OS specific),");
    	printf(" p (processor specific)\n");

	// Se lee la informacion de las cabeceras de programa    	
	// El offset inicial es donde empiezan las cabeceras de programa
    	offset = ehdr.e_phoff;

	// El offset maximo sera el offset inicial mas el producto del
	// numero de cabeceras de programa por su tamanho
    	max_offset = ehdr.e_phoff + ehdr.e_phnum * ehdr.e_phentsize;

    	phInfoTable = (Elf32_Phdr *) malloc(sizeof(Elf32_Phdr)*ehdr.e_phnum);

	programa = 0;
    	for (i = offset; i < max_offset; i += ehdr.e_phentsize) {
        	// Se posiciona en el offset de la cabecera de programa
		lseek(fd, i, SEEK_SET);

        	// Se leen los datos de la cabecera de programa
        	if (read(fd, &phdr, sizeof(Elf32_Phdr)) == -1) {
            		printf("Error al leer las cabeceras de programa del fichero %s\n", argv[1]);
            		close(fd);
            		exit(1);
        	}
		
		// Se almacenan los datos de la cabecera de programa
        	phInfoTable[programa].p_type = phdr.p_type;
        	phInfoTable[programa].p_offset = phdr.p_offset;
        	phInfoTable[programa].p_vaddr = phdr.p_vaddr;
        	phInfoTable[programa].p_paddr = phdr.p_paddr;
        	phInfoTable[programa].p_filesz = phdr.p_filesz;
        	phInfoTable[programa].p_memsz = phdr.p_memsz;
        	phInfoTable[programa].p_flags = phdr.p_flags;
        	phInfoTable[programa].p_align = phdr.p_align;
	
        	programa++;
    	}    	

	// Se imprimen las cabeceras de programa
        printf("\nProgram headers:\n");
    	printf("  %-14s %-8s %-10s %-10s %-7s %-7s %-3s %-5s\n",
		"Type","Offset","VirtAddr","PhysAddr", "FileSiz","MemSiz","Flg","Align");
	for (i = 0; i < ehdr.e_phnum; i++) {
        	printf("  %-14s 0x%06x 0x%08x 0x%08x 0x%05x 0x%05x %-3s 0x%x\n", getProgramType(phInfoTable[i].p_type),
               		phInfoTable[i].p_offset, phInfoTable[i].p_vaddr, phInfoTable[i].p_paddr, phInfoTable[i].p_filesz, 				phInfoTable[i].p_memsz, getProgramFlags(phInfoTable[i].p_flags), phInfoTable[i].p_align);
	        if (phInfoTable[i].p_type == PT_INTERP) {
            		char c;
            		printf("      [Requesting program interpreter: ");
            		lseek(fd, phInfoTable[i].p_offset, SEEK_SET);
            		do {
                		if (read(fd, &c, sizeof(char)) == -1) {
                    			printf("Error al leer el interprete de programa\n");
                    			close(fd);
                    			exit(1);
                		}
                		if (c != '\0') printf("%c",c);
            		} while (c != '\0');
            		printf("]\n");
        	}
    	}
	printf("\n Section to segment mapping:\n  Segment Sections...\n");
    	for (i = 0; i < ehdr.e_phnum; i++) {
        	printf("   %02d     ", i);
        	for (j = 0; j < ehdr.e_shnum; j++) {
            		if ((shInfoTable[j].sh_addr >= phInfoTable[i].p_vaddr)
                		&& ((shInfoTable[j].sh_addr+shInfoTable[j].sh_size)
                    		<= phInfoTable[i].p_vaddr+phInfoTable[i].p_memsz)) {
                			printf("%s ", getSectionName(shInfoTable[j].sh_name));
            		}
        	}
        	printf("\n");
    	}

	// Se cierra el fichero 
    	close(fd);
	
	//Se sale del programa
    	return 0;
}


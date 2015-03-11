#!/usr/bin/awk -f
# sample awk file to make C table source
BEGIN {
    FS=", *"
    first = 1;
    count = 0;
    mexp = ARGV[1];
    delete ARGV[1];
}
END {
    printf("\n};\n");
    printf("const int mt%sdc_params_%s_num  = %d;\n", w, mexp, count);
}

/^#/ {next}
{
    aaa = $1;
    mm = $2;
    nn = $3;
    rr = $4;
    w = $5;
    wmask = $6;
    umask = $7;
    lmask = $8;
    shift0 = $9;
    shift1 = $10;
    shiftB = $11;
    shiftC = $12;
    maskB = $13;
    maskC = $14;
    if (first) {
	first = 0;
	first_out();
    }
    middle_out();
}

function first_out() {
    printf("#include <stdint.h>\n");
    printf("#include \"mtdc%s.h\"\n", w);
    printf("#define MTDC_MEXP %s\n", mexp);
    printf("#define MTDC_N %s\n", nn);
    printf("#define MTDC_M %s\n", mm);
    printf("#define MTDC_UPPER_MASK 0x%sU\n", umask);
    printf("#define MTDC_LOWER_MASK 0x%sU\n", lmask);
    printf("#define MTDC_SHIFT0 %s\n", shift0);
    printf("#define MTDC_SHIFT1 %s\n", shift1);
    printf("#define MTDC_SHIFTB %s\n", shiftB);
    printf("#define MTDC_SHIFTC %s\n", shiftC);
    printf("#define MTDC_PARAM_TABLE mt%sdc_params_%s\n", w, mexp);
    printf("\n");
    printf("mt%s_params_t mt%sdc_params_%s[]\n = {", w, w, mexp);
    connect = "\n";
}

function middle_out() {
    printf("%s", connect);
    printf("    {0x%s,\n", aaa);
    printf("     0x%s,\n", maskB);
    printf("     0x%s}", maskC);
    connect = ",\n";
    count++;
}


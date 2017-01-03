#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct ymm {
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t d;
} __attribute__ ((packed));

struct ymmn {
    struct ymm ymm0;
    struct ymm ymm1;
    struct ymm ymm2;
    struct ymm ymm3;

    struct ymm ymm4;
    struct ymm ymm5;
    struct ymm ymm6;
    struct ymm ymm7;

    struct ymm ymm8;
    struct ymm ymm9;
    struct ymm ymm10;
    struct ymm ymm11;

    struct ymm ymm12;
    struct ymm ymm13;
    struct ymm ymm14;
    struct ymm ymm15;
} __attribute__ ((packed));

typedef union {
    uint8_t b[10];
    uint16_t s[5];
    //long double ld; // Why long double occupies 16 bytes?
} llf;

struct fxstate {
    uint16_t fcw;
    uint16_t fsw;
    uint8_t r00[28];
    llf st0;
    uint8_t r0[6];
    llf st1;
    uint8_t r1[6];
    llf st2;
    uint8_t r2[6];
    llf st3;
    uint8_t r3[6];
    llf st4;
    uint8_t r4[6];
    llf st5;
    uint8_t r5[6];
    llf st6;
    uint8_t r6[6];
    llf st7;
    uint8_t r7[6];
    uint8_t r01[512 - 160];
} __attribute__ ((packed));

struct regs {
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;

    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t rsp;

    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;

    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;

    union {
        struct ymm ymms[16];
        struct ymmn ymmn;
    };

    struct fxstate fxstate;
} __attribute__ ((packed));

size_t astrlen(const char *str);

void adump(struct regs *r);

void dump_regs() {
    struct regs *r = aligned_alloc(64, sizeof(*r));
    adump(r);

    printf("rax %016lx    rsi %016lx\n", r->rax, r->rsi);
    printf("rbx %016lx    rdi %016lx\n", r->rbx, r->rdi);
    printf("rcx %016lx    rbp %016lx\n", r->rcx, r->rbp);
    printf("rdx %016lx    rsp %016lx\n", r->rdx, r->rsp);

    printf("r8  %016lx    r12 %016lx\n", r->r8, r->r12);
    printf("r9  %016lx    r13 %016lx\n", r->r9, r->r13);
    printf("r10 %016lx    r14 %016lx\n", r->r10, r->r14);
    printf("r11 %016lx    r15 %016lx\n", r->r11, r->r15);

    printf("\n");

    printf("st0 %04hx%04hx%04hx%04hx%04hx\n",
           r->fxstate.st0.s[0],
           r->fxstate.st0.s[1],
           r->fxstate.st0.s[2],
           r->fxstate.st0.s[3],
           r->fxstate.st0.s[4]);
    printf("st1 %04hx%04hx%04hx%04hx%04hx\n",
           r->fxstate.st1.s[0],
           r->fxstate.st1.s[1],
           r->fxstate.st1.s[2],
           r->fxstate.st1.s[3],
           r->fxstate.st1.s[4]);
    printf("st2 %04hx%04hx%04hx%04hx%04hx\n",
           r->fxstate.st2.s[0],
           r->fxstate.st2.s[1],
           r->fxstate.st2.s[2],
           r->fxstate.st2.s[3],
           r->fxstate.st2.s[4]);
    printf("st3 %04hx%04hx%04hx%04hx%04hx\n",
           r->fxstate.st3.s[0],
           r->fxstate.st3.s[1],
           r->fxstate.st3.s[2],
           r->fxstate.st3.s[3],
           r->fxstate.st3.s[4]);
    printf("st4 %04hx%04hx%04hx%04hx%04hx\n",
           r->fxstate.st4.s[0],
           r->fxstate.st4.s[1],
           r->fxstate.st4.s[2],
           r->fxstate.st4.s[3],
           r->fxstate.st4.s[4]);
    printf("st5 %04hx%04hx%04hx%04hx%04hx\n",
           r->fxstate.st5.s[0],
           r->fxstate.st5.s[1],
           r->fxstate.st5.s[2],
           r->fxstate.st5.s[3],
           r->fxstate.st5.s[4]);
    printf("st6 %04hx%04hx%04hx%04hx%04hx\n",
           r->fxstate.st6.s[0],
           r->fxstate.st6.s[1],
           r->fxstate.st6.s[2],
           r->fxstate.st6.s[3],
           r->fxstate.st6.s[4]);
    printf("st7 %04hx%04hx%04hx%04hx%04hx\n",
           r->fxstate.st7.s[0],
           r->fxstate.st7.s[1],
           r->fxstate.st7.s[2],
           r->fxstate.st7.s[3],
           r->fxstate.st7.s[4]);

    printf("\n");

    for (int i = 0; i < 16; i++) {
        printf("ymm%02d %016lx %016lx %016lx %016lx\n", i,
               r->ymms[i].a, r->ymms[i].b, r->ymms[i].c, r->ymms[i].d);
    }
}

void str_demo() {
    char *s = "Hello world";
    size_t alen = astrlen(s);
    size_t slen = strlen(s);
    printf("alen: %lu\n", alen);
    printf("slen: %lu\n", slen);
}

void matrix_multiply(double *a, double *b, double *c, int n);

void matrix_demo() {
    int N = 2000;
    double *A = malloc(N * N * sizeof(*A));
    double *B = malloc(N * N * sizeof(*B));
    double *C = malloc(N * N * sizeof(*C));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = B[i * N + j] = 1.0;
        }
    }
    matrix_multiply(A, B, C, N);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%8lg ", C[i * N + j]);
        }
        printf("\n");
    }
}

int main() {
    matrix_demo();
    return 0;
}
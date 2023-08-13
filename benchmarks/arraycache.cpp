#include <benchmark/benchmark.h>

// m1 pro cache line size is 128, so rather similar performance for step size 8,16,32
// then performance proportional to step size after 32, 64, etc

// m1 pro L2 cache size is 4MiB, so array size above and below 4MiB would have difference effect
// for step size above 32 with larger than 4MiB arrays, speed seems to suffers from associativity.
// step 32 becomes much slower than 16

// For intel processors, we may see the effect of associativity much earlier due to smaller L2 cache size
// the testing machine has L2 size 2MiB. so array above 2MiB would see performance drop at step 16
// intel associativity is 16, cache line size 16

// size_t const ARR_SIZE = 16 * 1024 * 1024;
size_t const ARR_SIZE = 4 * 1024 * 1024;

uint32_t nums[ARR_SIZE];

static void DoSetup(const benchmark::State& state) {
    memset(nums, 0, sizeof(uint32_t) * ARR_SIZE);
}

static void DoTeardown(const benchmark::State& state) {
}

static void BM_ArrayAddition(benchmark::State& state) {
    uint32_t arr[ARR_SIZE] = {0};
    for (auto _ : state) {
        for (size_t i = 0; i < ARR_SIZE; i++) {
            arr[i]++;
        }
    }
}

static void BM_ArrayAdditionSkip(benchmark::State& state) {
    size_t step = state.range(0);
    size_t i = 0;
    for (auto _ : state) {
        for (size_t i = 0; i < ARR_SIZE; i+=step) {
            nums[i]++;
        }
    }
}

static void BM_ArrayMultiplicationSkip(benchmark::State& state) {
    size_t step = state.range(0);
    size_t i = 0;
    for (auto _ : state) {
        for (size_t i = 0; i < ARR_SIZE; i+=step) {
            nums[i]*=3;
        }
    }
}

// BENCHMARK(BM_ArrayAddition)->Setup(DoSetup)->Teardown(DoTeardown);

// m1 arm64 has 128-byte cacheline, while amd64 has 64-byute.

BENCHMARK(BM_ArrayAdditionSkip)->Arg(1)->Arg(4)->Arg(8)->Arg(16)->Arg(32)->Arg(64)->Arg(128)->Arg(256)->Setup(DoSetup)->Teardown(DoTeardown);

BENCHMARK(BM_ArrayMultiplicationSkip)->Arg(1)->Arg(4)->Arg(8)->Arg(16)->Arg(32)->Arg(64)->Arg(128)->Arg(256)->Setup(DoSetup)->Teardown(DoTeardown);

BENCHMARK_MAIN();
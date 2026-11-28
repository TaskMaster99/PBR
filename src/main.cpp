#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <chrono>
#include <ios>
#include <algorithm>
#include <numeric>
#include <filesystem>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

namespace fs = std::filesystem;


#define MiB(a) a * 1024 * 1024

std::optional<std::string> LoadCharFile(const char* filepath)
{
    std::ifstream file{filepath};

    if(file.is_open() == false)
    {
        std::fprintf(stderr ,"Error details : %s\n",std::strerror(errno));
        return {};
    }

    std::string buffer;
    
    char c;
    while(file.get(c))
    {
        buffer += c;
    }

    if(file.bad())
    {
        std::fprintf(stderr ,"Error details : %s\n",std::strerror(errno));
        return {};
    }

    return buffer;
}

std::optional<std::string> LoadLineFile(const char* filepath)
{
    std::ifstream file{filepath};

    if(file.is_open() == false)
    {
        std::fprintf(stderr ,"Error details : %s\n",std::strerror(errno));
        return {};
    }


    std::string buffer{};

    std::string lineBuffer{};

    while(std::getline(file ,lineBuffer, '\n'))
    {
        buffer.append(lineBuffer);
        if(!file.eof())
            buffer.append("\n");
    }

    if(file.bad())
    {
        std::fprintf(stderr ,"Error details : %s\n",std::strerror(errno));
        return {};
    }

    return buffer;
}

std::optional<std::string> LoadBulkFile(const char* filepath)
{
    std::ifstream file{filepath, std::ios::binary | std::ios::ate};
    if(file.is_open() == false)
    {
        std::fprintf(stderr ,"Error details : %s\n",std::strerror(errno));
        return {};
    }

    std::string buffer;

    const std::streamsize file_size = static_cast<std::streamsize>(file.tellg());
    if(file_size < 0)
    {
        std::fprintf(stderr ,"Failed to retrieve file size.\n");
        return {};
    }
    else if(buffer.max_size() < static_cast<std::size_t>(file_size))
    {
        std::fprintf(stderr ,"The file size exceed the capacity of the buffer.\n");
        return {};
    }
    else if(file.bad())
    {
        std::fprintf(stderr ,"Error details : %s\n",std::strerror(errno));
        return {};
    }

    buffer.resize(file_size);

    file.seekg(0);
    if(file.fail())
    {
        std::fprintf(stderr ,"Error details : %s\n",std::strerror(errno));
        return {};
    }

    file.read(buffer.data(), file_size);
    if(file.fail())
    {
        std::fprintf(stderr ,"Error details : %s\n",std::strerror(errno));
        return {};
    }

    return buffer;
}

std::optional<std::string> LoadBulkOptFile(const char* filepath)
{
    std::ifstream file{filepath, std::ios::binary | std::ios::ate};

    if(file.is_open() == false)
    {
        std::fprintf(stderr ,"Error details : %s\n",std::strerror(errno));
        return {};
    }
    std::string buffer;
    const std::streamsize file_size = static_cast<std::streamsize>(file.tellg());

    if(file_size < 0)
    {
        std::fprintf(stderr ,"Failed to retrieve file size.\n");
        return {};
    }
    else if(buffer.max_size() < static_cast<std::size_t>(file_size))
    {
        std::fprintf(stderr ,"The file size exceed the capacity of the buffer.\n");
        return {};
    }

    file.seekg(0);
    if(file.fail())
    {
        std::fprintf(stderr ,"Error details : %s\n",std::strerror(errno));
        return {};
    }

    buffer.resize_and_overwrite(static_cast<std::size_t>(file_size), [&](char* c, std::streamsize n) -> std::streamsize
    {
        file.read(c, n);
        return file.gcount();
    });

    if(file.fail())
    {
        std::fprintf(stderr ,"Error details : %s\n",std::strerror(errno));
        return {};
    }

    return buffer;
}


std::optional<std::string> LoadBulkOpt2File(const char* filepath)
{
    int file = open(filepath, O_RDONLY | O_CLOEXEC);
    if(file < 0)
    {
        std::fprintf(stderr ,"Error details : %s\n",std::strerror(errno));
        return {};
    }

    struct stat info{};

    int status = fstat(file, &info);
    if(status < 0)
    {
        std::fprintf(stderr ,"Error details : %s\n",std::strerror(errno));
        return {};
    }

    std::string buffer;
    const ssize_t file_size = info.st_size;

    if(file_size < 0)
    {
        std::fprintf(stderr ,"Failed to retrieve file size.\n");
        return {};
    }
    else if(buffer.max_size() < static_cast<std::size_t>(file_size))
    {
        std::fprintf(stderr ,"The file size exceed the capacity of the buffer.\n");
        return {};
    }

    buffer.resize_and_overwrite(static_cast<std::size_t>(file_size), [&](char* c, ssize_t n) -> ssize_t
    {
        return read(file, c, n);
    });

    return buffer;
}


struct BenchmarkResult
{

    std::double_t min_time;
    std::double_t max_time;
    std::double_t mean_time;
    std::double_t median_time;
    std::double_t throughtput;
};

void warmUp()
{
    for(auto i = 0ULL; i < 20; ++i)
    {
        auto buffer = LoadBulkFile("meshes/very_large.obj");
    }
}

template<typename Loader>
BenchmarkResult Benchmark(Loader& loader, const char* filepath, const std::uint64_t nsamples)
{
    std::vector<std::double_t> samples(nsamples);

    for(auto i = 0ULL; i < nsamples; ++i)
    {
        auto t0 = std::chrono::steady_clock::now();
        auto buffer = loader(filepath);
        auto t1 = std::chrono::steady_clock::now();

        samples[i] = std::chrono::duration<std::double_t, std::milli>(t1 - t0).count();
    }

    std::sort(samples.begin(), samples.end());

    std::double_t min = samples[0];
    std::double_t max = samples[nsamples-1];

    std::double_t mean = std::accumulate(samples.begin(), samples.end(), 0.0) / nsamples;

    std::double_t median = nsamples % 2 ? samples[(nsamples - 1)/2] : (samples[(nsamples)/2] + samples[(nsamples)/2 - 1])/2; 

    const std::double_t size = fs::file_size(filepath);
    std::double_t throughtput = ((size / (1024.0 * 1024.0 * 1024.0)) / (median / 1000.0));

    return {min, max, mean, median, throughtput};
}

void printBench(const BenchmarkResult& bm, const char* name)
{
    std::printf("|name    |min       (ms)|max      (ms)|mean      (ms)|median         (ms)|throughtput     (GiB/s)|\n");
    std::printf("|%s    |%lf     |%lf   |%lf   |%lf       |%lf   |\n", name, bm.min_time, bm.max_time, bm.mean_time, bm.median_time, bm.throughtput);

}

void benchAll()
{
    auto bulkBenchSmall = Benchmark(LoadBulkFile, "meshes/small.obj", 100);
    auto bulkBenchMedium = Benchmark(LoadBulkFile, "meshes/medium.obj", 100);
    auto bulkBenchLarge = Benchmark(LoadBulkFile, "meshes/large.obj", 100);
    auto bulkBenchVeryLarge = Benchmark(LoadBulkFile, "meshes/very_large.obj", 100);

    printBench(bulkBenchSmall, "bulk-small");
    printBench(bulkBenchMedium, "bulk-med");
    printBench(bulkBenchLarge, "bulk-large");
    printBench(bulkBenchVeryLarge, "bulk-vlarge");

    printf("\n");
    printf("\n");

    auto bulkOptBenchSmall = Benchmark(LoadBulkOptFile, "meshes/small.obj", 100);
    auto bulkOptBenchMedium = Benchmark(LoadBulkOptFile, "meshes/medium.obj", 100);
    auto bulkOptBenchLarge = Benchmark(LoadBulkOptFile, "meshes/large.obj", 100);
    auto bulkOptBenchVeryLarge = Benchmark(LoadBulkOptFile, "meshes/very_large.obj", 100);

    printBench(bulkOptBenchSmall, "bulk-opt-small");
    printBench(bulkOptBenchMedium, "bulk-opt-med");
    printBench(bulkOptBenchLarge, "bulk-opt-large");
    printBench(bulkOptBenchVeryLarge, "bulk-opt-vlarge");

    printf("\n");
    printf("\n");


    auto bulkOpt2BenchSmall = Benchmark(LoadBulkOpt2File, "meshes/small.obj", 100);
    auto bulkOpt2BenchMedium = Benchmark(LoadBulkOpt2File, "meshes/medium.obj", 100);
    auto bulkOpt2BenchLarge = Benchmark(LoadBulkOpt2File, "meshes/large.obj", 100);
    auto bulkOpt2BenchVeryLarge = Benchmark(LoadBulkOpt2File, "meshes/very_large.obj", 100);

    printBench(bulkOpt2BenchSmall, "bulk-opt2-small");
    printBench(bulkOpt2BenchMedium, "bulk-opt2-med");
    printBench(bulkOpt2BenchLarge, "bulk-opt2-large");
    printBench(bulkOpt2BenchVeryLarge, "bulk-opt2-vlarge");

    printf("\n");
    printf("\n");

/*     auto charBenchSmall = Benchmark(LoadCharFile, "meshes/small.obj", 100);
    auto charBenchMedium = Benchmark(LoadCharFile, "meshes/medium.obj", 100);
    auto charBenchLarge = Benchmark(LoadCharFile, "meshes/large.obj", 100);
    auto charBenchVeryLarge = Benchmark(LoadCharFile, "meshes/very_large.obj", 100);

    printBench(charBenchSmall, "char-small");
    printBench(charBenchMedium, "char-med");
    printBench(charBenchLarge, "char-large");
    printBench(charBenchVeryLarge, "char-vlarge");


    auto lineBenchSmall = Benchmark(LoadLineFile, "meshes/small.obj", 100);
    auto lineBenchMedium = Benchmark(LoadLineFile, "meshes/medium.obj", 100);
    auto lineBenchLarge = Benchmark(LoadLineFile, "meshes/large.obj", 100);
    auto lineBenchVeryLarge = Benchmark(LoadLineFile, "meshes/very_large.obj", 100);

    printBench(lineBenchSmall, "line-small");
    printBench(lineBenchMedium, "line-med");
    printBench(lineBenchLarge, "line-large");
    printBench(lineBenchVeryLarge, "line-vlarge"); */
}

int main()
{
    warmUp();
    benchAll();

    //auto optbulk = LoadBulkOptFile("meshes/triangle.obj");
    //std::printf("%s\n", optbulk.value().data());

    //auto file = LoadBulkOpt2File("meshes/triangle.obj");
    //std::printf("%s\n", file.value().data());
}
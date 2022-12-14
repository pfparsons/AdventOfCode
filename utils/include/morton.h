#include <cstdint>

static inline uint64_t interleave_uint32_with_zeros(uint32_t input)  {
    uint64_t word = input;
    word = (word ^ (word << 16)) & 0x0000ffff0000ffff;
    word = (word ^ (word << 8 )) & 0x00ff00ff00ff00ff;
    word = (word ^ (word << 4 )) & 0x0f0f0f0f0f0f0f0f;
    word = (word ^ (word << 2 )) & 0x3333333333333333;
    word = (word ^ (word << 1 )) & 0x5555555555555555;
    return word;
}

static inline uint32_t interleave_uint16_with_zeros(uint16_t input)  {
    uint64_t word = input;
    word = (word ^ (word << 8 )) & 0x00ff00ff;
    word = (word ^ (word << 4 )) & 0x0f0f0f0f;
    word = (word ^ (word << 2 )) & 0x33333333;
    word = (word ^ (word << 1 )) & 0x55555555;
    return word;
}

static inline uint32_t deinterleave_lowuint32(uint64_t word) {
    word &= 0x5555555555555555;
    word = (word ^ (word >> 1 )) & 0x3333333333333333;
    word = (word ^ (word >> 2 )) & 0x0f0f0f0f0f0f0f0f;
    word = (word ^ (word >> 4 )) & 0x00ff00ff00ff00ff;
    word = (word ^ (word >> 8 )) & 0x0000ffff0000ffff;
    word = (word ^ (word >> 16)) & 0x00000000ffffffff;
    return (uint32_t)word;
}

static inline uint16_t deinterleave_lowuint16(uint32_t word) {
	word &= 0x55555555;
    word = (word ^ (word >> 1 )) & 0x3333333;
    word = (word ^ (word >> 2 )) & 0x0f0f0f0f;
    word = (word ^ (word >> 4 )) & 0x00ff00ff;
    word = (word ^ (word >> 8 )) & 0x0000ffff;
    return (uint16_t)word;
}

typedef struct  {
  uint32_t x;
  uint32_t y;
} point32;

typedef struct  {
  uint16_t x;
  uint16_t y;
} point16;

uint64_t interleave32(point32 input)  {
    return interleave_uint32_with_zeros(input.x) | (interleave_uint32_with_zeros(input.y) << 1);
}

point32 deinterleave32(uint64_t input)  {
  point32 answer;
  answer.x = deinterleave_lowuint32(input);
  answer.y = deinterleave_lowuint32(input>>1);
  return answer;
}

uint64_t interleave16(point32 input)  {
    return interleave_uint32_with_zeros(input.x) | (interleave_uint32_with_zeros(input.y) << 1);
}

point32 deinterleave16(uint64_t input)  {
  point32 answer;
  answer.x = deinterleave_lowuint32(input);
  answer.y = deinterleave_lowuint32(input>>1);
  return answer;
}



constexpr uint32_t bits = 4;
constexpr uint32_t limx = (1 << bits) * 2;
uint32_t db[limx];

int cnt = 1;

void lpad(int w, std::string &str) {
	str.insert(str.begin(), w - str.length(), ' ');
}

int main() {
	db[0] = 0;
	for(auto i = 0u; i <= bits; i++) {
		int pos = cnt;
		uint32_t pow4 = 1u << (i * 2);
		for(auto j = 0; j < pos; j++) {
			db[cnt] = pow4 + db[j];
			cnt++;
		}
	}
	printf("limx %u\n", limx);

	int div_w = (limx + 1) * 4 + limx - 5;
	auto div_x = std::string(div_w, '-');
	printf("       ");
	for(auto x = 0u; x < limx; x++) {
		auto xs = std::to_string(x);
		lpad(4, xs);
		printf("%s ", xs.c_str());
	}
	printf("\n       %s\n", div_x.c_str());
	
	for(auto y = 0u; y < limx; y++) {
		auto yc = std::to_string(y);
		lpad(4, yc);
		printf("%s | ", yc.c_str());
		for(auto x = 0; x < limx; x++) {
			uint32_t db_x = db[x];
			uint32_t db_y = db[y] * 2;
			uint32_t db_v = db_x + db_y;
			//printf("%u,%u = %u,%u = %u\n",x,y, db_x, db_y, db);
			printf("%04u ", db_v);
		}
		printf("\n");
	}
}

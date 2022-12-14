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

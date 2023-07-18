input [3:0] numeral_bit;

output a;
output b;
output c;
output d;
output e;
output f;
output g;

wire not_numeral_bit_3;
wire not_numeral_bit_2;
wire not_numeral_bit_1;
wire not_numeral_bit_0;

wire not_3_and_not_2;
wire not_1_and_not_0;

wire minterm_00;
wire minterm_01;
wire minterm_02;
wire minterm_03;
wire minterm_04;
wire minterm_05;
wire minterm_06;
wire minterm_07;
wire minterm_08;
wire minterm_09;

wire minterm_00_or_minterm_02;
wire minterm_06_or_minterm_08;

assign not_numeral_bit_3 = ~ numeral_bit[3];
assign not_numeral_bit_2 = ~ numeral_bit[2];
assign not_numeral_bit_1 = ~ numeral_bit[1];
assign not_numeral_bit_0 = ~ numeral_bit[0];

assign minterm_00 = not_numeral_bit_3 & not_numeral_bit_2;
assign minterm_00 = minterm_00 & not_numeral_bit_1;
assign minterm_00 = minterm_00 & not_numeral_bit_0;

assign minterm_01 = not_numeral_bit_3 & not_numeral_bit_2;
assign minterm_01 = minterm_01 & not_numeral_bit_1;
assign minterm_01 = minterm_01 & numeral_bit[0];

assign minterm_02 = not_numeral_bit_3 & not_numeral_bit_2;
assign minterm_02 = minterm_02  & numeral_bit[1];
assign minterm_02 = minterm_02 & not_numeral_bit_0;

assign minterm_03 = not_numeral_bit_3 & not_numeral_bit_2;
assign minterm_03 = minterm_03 & numeral_bit[1];
assign minterm_03 = minterm_03 & numeral_bit[0];

assign minterm_04 = not_numeral_bit_3 & numeral_bit[2];
assign minterm_04 = minterm_04 & not_numeral_bit_1;
assign minterm_04 = minterm_04 & not_numeral_bit_0;

assign minterm_05 = not_numeral_bit_3  & numeral_bit[2];
assign minterm_05 = minterm_05 & not_numeral_bit_1;
assign minterm_05 = minterm_05 & numeral_bit[0];

assign minterm_06 = not_numeral_bit_3 & numeral_bit[2];
assign minterm_06 = minterm_06 & numeral_bit[1];
assign minterm_06 = minterm_06 & not_numeral_bit_0;

assign minterm_07 = not_numeral_bit_3 & numeral_bit[2];
assign minterm_07 = minterm_07 & numeral_bit[1];
assign minterm_07 = minterm_07 & numeral_bit[0];

assign minterm_08 = numeral_bit[3] & not_numeral_bit_2;
assign minterm_08 = minterm_08 & not_numeral_bit_1;
assign minterm_08 = minterm_08 & not_numeral_bit_0;

assign minterm_09 = numeral_bit[3] & not_numeral_bit_2;
assign minterm_09 = minterm_09 & not_numeral_bit_1;
assign minterm_09 = minterm_09 & numeral_bit[0];

assign a = minterm_00 | minterm_02;
assign a = a | minterm_03;
assign a = a | minterm_05;
assign a = a | minterm_06;
assign a = a | minterm_08;
assign a = a | minterm_07;
assign a = a | minterm_09;

assign b = minterm_00 | minterm_01 
assign b = b | minterm_02;
assign b = b | minterm_03;
assign b = b | minterm_04;
assign b = b | minterm_07;
assign b = b | minterm_08;
assign b = b | minterm_09;

assign c = minterm_00 | minterm_01;
assign c = c | minterm_03;
assign c = c | minterm_04;
assign c = c | minterm_05;
assign c = c | minterm_06;
assign c = c | minterm_08;
assign c = c | minterm_07;
assign c = c | minterm_09

assign d = minterm_00 | minterm_02;
assign d = d | minterm_03;
assign d = d | minterm_05;
assign d = d | minterm_06;
assign d = d | minterm_08;
assign d = d | minterm_09;

assign e = minterm_00 | minterm_02;
assign e = e | minterm_06;
assign e = e | minterm_08;

assign f = minterm_00 | minterm_04;
assign f = f | minterm_05;
assign f = f | minterm_06;
assign f = f | minterm_08;
assign f = f | minterm_09;

assign g = minterm_02 | minterm_03;
assign g = g | minterm_03;
assign g = g | minterm_04;
assign g = g | minterm_05;
assign g = g | minterm_08;
assign g = g | minterm_06;
assign g = g | minterm_09;
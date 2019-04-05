include "shared.thrift"

namespace cpp calc

const i32 MAGIC = 0x55AA;
const map<string, string> SIGNATURE = {
'author': 'oxnz',
'timestamp': '2019-04-05'
}

enum Operation {
ADD = 1,
SUB = 2,
MUL = 3,
DIV = 4
}

struct Work {
1: i32 r1 = 0,
2: i32 r2,
3: Operation op,
4: optional string note,
}

exception InvalidOperation {
1: i32 op,
2: string repr
}

service Calculator extends shared.SharedService {
void ping(),
i32 add(1:i32 r1, 2:i32 r2),
i32 calc(1:i32 seq, 2:Work w) throws (1:InvalidOperation e),
oneway void zip()
}

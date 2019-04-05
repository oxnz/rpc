namespace cpp shared

struct SharedStruct {
1: i32 key
2: string value
}

service SharedService {
SharedStruct getStruct(1: i32 key)
string echo(1: string s)
}

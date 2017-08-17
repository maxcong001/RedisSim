#include "redisSim/util.h"
namespace RSim
{
msg_c2s unpack_msg_c2s(char *buff)
{
    msg_c2s ret;
    type_c2s *tmp = (type_c2s *)buff;
    ret.type = *tmp;
    tmp++;
    uint32_t *tmp_len = (uint32_t *)tmp;
    ret.len = *tmp_len;
    tmp_len++;
    ret.msg = (void *)tmp_len;
    __LOG(debug, " unpack message: type is " << ret.type << " length is " << ret.len << " message is " << std::string((char *)(ret.msg), ret.len));

    return ret;
}
std::string pack_msg_c2s(type_c2s type, const char *msg, uint32_t len)
{
    type_c2s tmp = type;
    uint32_t tmp_len = len;
    return std::string((char *)(&tmp), sizeof(type_c2s)) + std::string((char *)(&tmp_len), sizeof(uint32_t)) + std::string(msg, len);
}
}
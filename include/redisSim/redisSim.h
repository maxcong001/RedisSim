#pragma once
#include <unordered_set>
#include "logger/logger.h"
#include "redisSim/util.h"
#include "redisSim/simForwarder.h"

namespace RSim
{
class redisSim
{
public:
  bool init();
  void add(forwarder_conn_info &info);
  bool delete_f(simForwarder *msgp);

private:
  std::unordered_set<simForwarder *> f_map;
  std::mutex mtx;
};
}
#pragma once

namespace pikiwidb {
class RedisTask {
 public:
  enum class OpType {
    kGet,
    kSet,
    kDel,
    kIncr,
    kDecr,
    kUnknown,
  };

  RedisTask() = default;
  virtual ~RedisTask() = 0;

  virtual void Execute() = 0;
  virtual void CallBack() = 0;
  OpType GetOpType() const { return op_type_; }

 private:
  OpType op_type_ = OpType::kUnknown;
};
}  // namespace pikiwidb
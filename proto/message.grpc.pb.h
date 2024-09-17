// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: message.proto
#ifndef GRPC_message_2eproto__INCLUDED
#define GRPC_message_2eproto__INCLUDED

#include "message.pb.h"

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/proto_utils.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/stub_options.h>
#include <grpcpp/support/sync_stream.h>

namespace message {

class VerifyService final {
 public:
  static constexpr char const* service_full_name() {
    return "message.VerifyService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status GetVerifyCode(::grpc::ClientContext* context, const ::message::GetVerifyRequest& request, ::message::GetVerifyResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::message::GetVerifyResponse>> AsyncGetVerifyCode(::grpc::ClientContext* context, const ::message::GetVerifyRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::message::GetVerifyResponse>>(AsyncGetVerifyCodeRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::message::GetVerifyResponse>> PrepareAsyncGetVerifyCode(::grpc::ClientContext* context, const ::message::GetVerifyRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::message::GetVerifyResponse>>(PrepareAsyncGetVerifyCodeRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void GetVerifyCode(::grpc::ClientContext* context, const ::message::GetVerifyRequest* request, ::message::GetVerifyResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void GetVerifyCode(::grpc::ClientContext* context, const ::message::GetVerifyRequest* request, ::message::GetVerifyResponse* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::message::GetVerifyResponse>* AsyncGetVerifyCodeRaw(::grpc::ClientContext* context, const ::message::GetVerifyRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::message::GetVerifyResponse>* PrepareAsyncGetVerifyCodeRaw(::grpc::ClientContext* context, const ::message::GetVerifyRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status GetVerifyCode(::grpc::ClientContext* context, const ::message::GetVerifyRequest& request, ::message::GetVerifyResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::message::GetVerifyResponse>> AsyncGetVerifyCode(::grpc::ClientContext* context, const ::message::GetVerifyRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::message::GetVerifyResponse>>(AsyncGetVerifyCodeRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::message::GetVerifyResponse>> PrepareAsyncGetVerifyCode(::grpc::ClientContext* context, const ::message::GetVerifyRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::message::GetVerifyResponse>>(PrepareAsyncGetVerifyCodeRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void GetVerifyCode(::grpc::ClientContext* context, const ::message::GetVerifyRequest* request, ::message::GetVerifyResponse* response, std::function<void(::grpc::Status)>) override;
      void GetVerifyCode(::grpc::ClientContext* context, const ::message::GetVerifyRequest* request, ::message::GetVerifyResponse* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::message::GetVerifyResponse>* AsyncGetVerifyCodeRaw(::grpc::ClientContext* context, const ::message::GetVerifyRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::message::GetVerifyResponse>* PrepareAsyncGetVerifyCodeRaw(::grpc::ClientContext* context, const ::message::GetVerifyRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_GetVerifyCode_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status GetVerifyCode(::grpc::ServerContext* context, const ::message::GetVerifyRequest* request, ::message::GetVerifyResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_GetVerifyCode : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_GetVerifyCode() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_GetVerifyCode() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetVerifyCode(::grpc::ServerContext* /*context*/, const ::message::GetVerifyRequest* /*request*/, ::message::GetVerifyResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetVerifyCode(::grpc::ServerContext* context, ::message::GetVerifyRequest* request, ::grpc::ServerAsyncResponseWriter< ::message::GetVerifyResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_GetVerifyCode<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_GetVerifyCode : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_GetVerifyCode() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::message::GetVerifyRequest, ::message::GetVerifyResponse>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::message::GetVerifyRequest* request, ::message::GetVerifyResponse* response) { return this->GetVerifyCode(context, request, response); }));}
    void SetMessageAllocatorFor_GetVerifyCode(
        ::grpc::MessageAllocator< ::message::GetVerifyRequest, ::message::GetVerifyResponse>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::message::GetVerifyRequest, ::message::GetVerifyResponse>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_GetVerifyCode() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetVerifyCode(::grpc::ServerContext* /*context*/, const ::message::GetVerifyRequest* /*request*/, ::message::GetVerifyResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* GetVerifyCode(
      ::grpc::CallbackServerContext* /*context*/, const ::message::GetVerifyRequest* /*request*/, ::message::GetVerifyResponse* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_GetVerifyCode<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_GetVerifyCode : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_GetVerifyCode() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_GetVerifyCode() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetVerifyCode(::grpc::ServerContext* /*context*/, const ::message::GetVerifyRequest* /*request*/, ::message::GetVerifyResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_GetVerifyCode : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_GetVerifyCode() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_GetVerifyCode() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetVerifyCode(::grpc::ServerContext* /*context*/, const ::message::GetVerifyRequest* /*request*/, ::message::GetVerifyResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetVerifyCode(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_GetVerifyCode : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_GetVerifyCode() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->GetVerifyCode(context, request, response); }));
    }
    ~WithRawCallbackMethod_GetVerifyCode() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetVerifyCode(::grpc::ServerContext* /*context*/, const ::message::GetVerifyRequest* /*request*/, ::message::GetVerifyResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* GetVerifyCode(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_GetVerifyCode : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_GetVerifyCode() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::message::GetVerifyRequest, ::message::GetVerifyResponse>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::message::GetVerifyRequest, ::message::GetVerifyResponse>* streamer) {
                       return this->StreamedGetVerifyCode(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_GetVerifyCode() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status GetVerifyCode(::grpc::ServerContext* /*context*/, const ::message::GetVerifyRequest* /*request*/, ::message::GetVerifyResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedGetVerifyCode(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::message::GetVerifyRequest,::message::GetVerifyResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_GetVerifyCode<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_GetVerifyCode<Service > StreamedService;
};

class StatusService final {
 public:
  static constexpr char const* service_full_name() {
    return "message.StatusService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status GetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerRequest& request, ::message::GetChatServerResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::message::GetChatServerResponse>> AsyncGetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::message::GetChatServerResponse>>(AsyncGetChatServerRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::message::GetChatServerResponse>> PrepareAsyncGetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::message::GetChatServerResponse>>(PrepareAsyncGetChatServerRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void GetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerRequest* request, ::message::GetChatServerResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void GetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerRequest* request, ::message::GetChatServerResponse* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::message::GetChatServerResponse>* AsyncGetChatServerRaw(::grpc::ClientContext* context, const ::message::GetChatServerRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::message::GetChatServerResponse>* PrepareAsyncGetChatServerRaw(::grpc::ClientContext* context, const ::message::GetChatServerRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status GetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerRequest& request, ::message::GetChatServerResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::message::GetChatServerResponse>> AsyncGetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::message::GetChatServerResponse>>(AsyncGetChatServerRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::message::GetChatServerResponse>> PrepareAsyncGetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::message::GetChatServerResponse>>(PrepareAsyncGetChatServerRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void GetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerRequest* request, ::message::GetChatServerResponse* response, std::function<void(::grpc::Status)>) override;
      void GetChatServer(::grpc::ClientContext* context, const ::message::GetChatServerRequest* request, ::message::GetChatServerResponse* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::message::GetChatServerResponse>* AsyncGetChatServerRaw(::grpc::ClientContext* context, const ::message::GetChatServerRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::message::GetChatServerResponse>* PrepareAsyncGetChatServerRaw(::grpc::ClientContext* context, const ::message::GetChatServerRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_GetChatServer_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status GetChatServer(::grpc::ServerContext* context, const ::message::GetChatServerRequest* request, ::message::GetChatServerResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_GetChatServer : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_GetChatServer() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_GetChatServer() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetChatServer(::grpc::ServerContext* /*context*/, const ::message::GetChatServerRequest* /*request*/, ::message::GetChatServerResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetChatServer(::grpc::ServerContext* context, ::message::GetChatServerRequest* request, ::grpc::ServerAsyncResponseWriter< ::message::GetChatServerResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_GetChatServer<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_GetChatServer : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_GetChatServer() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::message::GetChatServerRequest, ::message::GetChatServerResponse>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::message::GetChatServerRequest* request, ::message::GetChatServerResponse* response) { return this->GetChatServer(context, request, response); }));}
    void SetMessageAllocatorFor_GetChatServer(
        ::grpc::MessageAllocator< ::message::GetChatServerRequest, ::message::GetChatServerResponse>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::message::GetChatServerRequest, ::message::GetChatServerResponse>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_GetChatServer() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetChatServer(::grpc::ServerContext* /*context*/, const ::message::GetChatServerRequest* /*request*/, ::message::GetChatServerResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* GetChatServer(
      ::grpc::CallbackServerContext* /*context*/, const ::message::GetChatServerRequest* /*request*/, ::message::GetChatServerResponse* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_GetChatServer<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_GetChatServer : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_GetChatServer() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_GetChatServer() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetChatServer(::grpc::ServerContext* /*context*/, const ::message::GetChatServerRequest* /*request*/, ::message::GetChatServerResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_GetChatServer : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_GetChatServer() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_GetChatServer() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetChatServer(::grpc::ServerContext* /*context*/, const ::message::GetChatServerRequest* /*request*/, ::message::GetChatServerResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetChatServer(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_GetChatServer : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_GetChatServer() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->GetChatServer(context, request, response); }));
    }
    ~WithRawCallbackMethod_GetChatServer() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetChatServer(::grpc::ServerContext* /*context*/, const ::message::GetChatServerRequest* /*request*/, ::message::GetChatServerResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* GetChatServer(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_GetChatServer : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_GetChatServer() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::message::GetChatServerRequest, ::message::GetChatServerResponse>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::message::GetChatServerRequest, ::message::GetChatServerResponse>* streamer) {
                       return this->StreamedGetChatServer(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_GetChatServer() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status GetChatServer(::grpc::ServerContext* /*context*/, const ::message::GetChatServerRequest* /*request*/, ::message::GetChatServerResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedGetChatServer(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::message::GetChatServerRequest,::message::GetChatServerResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_GetChatServer<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_GetChatServer<Service > StreamedService;
};

}  // namespace message


#endif  // GRPC_message_2eproto__INCLUDED

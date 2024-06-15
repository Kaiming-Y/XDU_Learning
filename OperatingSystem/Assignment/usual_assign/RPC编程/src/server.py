import signal
import grpc
import logging
from concurrent import futures
import calculator_pb2
import calculator_pb2_grpc

logging.basicConfig(level=logging.INFO)

class CalculatorServicer(calculator_pb2_grpc.CalculatorServicer):
    def Multiply(self, request, context):
        operand1 = request.operand1
        operand2 = request.operand2
        logging.info(f"Received request: operand1={operand1}, operand2={operand2}")
        
        result = operand1 * operand2
        logging.info(f"Calculation result: {result}")
        
        return calculator_pb2.MultiplyResponse(result=result)

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    calculator_pb2_grpc.add_CalculatorServicer_to_server(
        CalculatorServicer(), server)
    server.add_insecure_port('[::]:50051')
    server.start()

    # 注册信号处理程序
    signal.signal(signal.SIGINT, lambda signum, frame: server.stop(0))

    logging.info("Server started. Listening on port 50051.")
    server.wait_for_termination()

if __name__ == '__main__':
    serve()


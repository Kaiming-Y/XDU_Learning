import grpc
import calculator_pb2
import calculator_pb2_grpc
import sys

def run(operand1, operand2):
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = calculator_pb2_grpc.CalculatorStub(channel)
        request = calculator_pb2.MultiplyRequest(
            operand1=operand1,
            operand2=operand2
        )
        response = stub.Multiply(request)
        print(f'Result: {response.result}')

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: python client.py <operand1> <operand2>")
        sys.exit(1)

    operand1 = int(sys.argv[1])
    operand2 = int(sys.argv[2])
    run(operand1, operand2)


from json import dumps
from main import solution

button = input("Enter 'RUN' or 'SUBMIT': ")
file_name = "run_cases.txt" if button == "RUN" else "submit_cases.txt"

try:
    with open(file_name) as f, open("result.json", "w") as out:
        results = []
        for i, line in enumerate(f, start=1):
            inputs = line.strip().split()
            a, b, expected_output = map(int, inputs)
            output = solution(a, b)
            result = output == expected_output
            results.append(result)
            result_dict = {
                "case": i,
                "input": [a, b],
                "expected_output": expected_output,
                "output": output,
                "result": result
            }
            out.write(dumps(result_dict) + "\n")
            if all(results):
                out.write(dumps({"success": True}))
            else:
                out.write(dumps({"success": False}))
except IOError:
    print("Error: File not found")

const readline = require("readline");
const solution = require("./main");
const fs = require("fs");

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

rl.question("Enter 'RUN' or 'SUBMIT': ", function (button) {
  let file_name;
  if (button === "RUN") {
    file_name = "run_cases.txt";
  } else if (button === "SUBMIT") {
    file_name = "submit_cases.txt";
  } else {
    console.log("Invalid input");
    rl.close();
    return;
  }

  const results = [];
  let line_count = 0;

  const fileStream = fs.createReadStream(file_name);
  const rl = readline.createInterface({
    input: fileStream,
    crlfDelay: Infinity,
  });

  const resultStream = fs.createWriteStream("result.txt");

  rl.on("line", (line) => {
    line_count++;
    const [a, b, c] = line.split(" ").map(Number);
    const trueSum = c;
    const yourSum = solution(a, b);
    const result = yourSum === trueSum;
    results.push(result);
    if (!result) {
      console.log(`Case ${line_count} is false`);
      console.log(`Expected: ${trueSum}`);
      console.log(`Output: ${yourSum}`);
      resultStream.write(`Case ${line_count} is false\n`);
      resultStream.write(`Expected: ${trueSum}\n`);
      resultStream.write(`Output: ${yourSum}\n`);
    }
  });

  rl.on("close", () => {
    const all_results = results.every((r) => r);
    if (all_results) {
      console.log("Success");
      resultStream.write("Success\n");
    } else {
      console.log("Failure");
      resultStream.write("Failure\n");
    }
    resultStream.end();
  });
});

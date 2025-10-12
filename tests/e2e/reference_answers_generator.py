import subprocess
from pathlib import Path

def generate_answers():
    script_dir = Path(__file__).parent
    executable = script_dir / "../../build/tests/e2e/run_reference"
    test_dir = script_dir / "test_data"
    
    if not executable.exists():
        print(f"Error: Not found {executable}")
        return
    
    for dat_file in test_dir.glob("*.dat"):
        ans_file = test_dir / f"{dat_file.stem}.ans"
        
        with open(dat_file, 'r') as fin, open(ans_file, 'w') as fout:
            subprocess.run([str(executable)], stdin=fin, stdout=fout)

if __name__ == "__main__":
    generate_answers()

import subprocess
import sys
import os

def run_test(args_str, input_file, expected_output_file):

    if not os.path.exists(input_file):
        print(f" Error: Input file '{input_file}' not found.")
        return
    if not os.path.exists(expected_output_file):
        print(f" Error: Expected output file '{expected_output_file}' not found.")
        return

    
    with open(input_file, 'r') as f:
        input_data = f.read()

   
    with open(expected_output_file, 'r') as f:
        expected_output = f.read().strip()

  
    cmd = [sys.executable, 'project.py'] + args_str.split()

    print(f"Testing: python project.py {args_str} < {input_file} ... ", end="")

    try:
    
        result = subprocess.run(
            cmd,
            input=input_data,       # הכנסת הקלט ל-stdin
            capture_output=True,    # תפיסת ה-stdout וה-stderr
            text=True               # עבודה עם מחרוזות ולא בייטים
        )

      
        actual_output = result.stdout.strip()

        # השוואה
        if actual_output == expected_output:
            print("✅ PASS")
        else:
            print("❌ FAIL")
            print("-" * 20)
            print(f"Expected:\n{expected_output[:100]}...") # מציג רק את ההתחלה
            print(f"Got:\n{actual_output[:100]}...")
            print("-" * 20)
            
            # בדיקה אם יש שגיאה (stderr)
            if result.stderr:
                print(f"Error Output:\n{result.stderr}")

    except Exception as e:
        print(f"\nExample crashed: {e}")

def main():
    # רשימת הטסטים: (ארגומנטים, קובץ קלט, קובץ פלט צפוי)
    tests = [
        ("3 600", "input_1.txt", "output_1.txt"),
        ("7",     "input_2.txt", "output_2.txt"),
        ("15 300", "input_3.txt", "output_3.txt")
    ]

    print("--- Starting Tests ---\n")
    
    for args, input_f, output_f in tests:
        run_test(args, input_f, output_f)
    
    print("\n--- Done ---")

if __name__ == '__main__':
    main()
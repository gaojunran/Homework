import os
import shutil
import subprocess
import unittest


def run_command(cmd):
    """Run a shell command, print and return the (exit_code, stdout, stderr)."""
    print(f"Running command: {cmd}")
    result = subprocess.run(
        cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE
    )
    stdout = result.stdout.decode()
    stderr = result.stderr.decode()
    print(f"Exit Code: {result.returncode}")
    if stdout:
        print(f"STDOUT:\n{stdout}")
    if stderr:
        print(f"STDERR:\n{stderr}")
    return result.returncode, stdout, stderr


class TestCopyMoveCommands(unittest.TestCase):

    # Run only once before all tests
    @classmethod
    def setUpClass(cls):
        os.makedirs("demo", exist_ok=True)

    # Run before each test
    def setUp(self):
        for filename in os.listdir("demo"):
            filepath = os.path.join("demo", filename)
            if os.path.isfile(filepath) or os.path.islink(filepath):
                os.unlink(filepath)
            elif os.path.isdir(filepath):
                shutil.rmtree(filepath)

    def test_1_no_argument(self):
        code, _, _ = run_command("./copy")
        self.assertNotEqual(code, 0)

    def test_2_one_argument(self):
        code, _, _ = run_command("./copy ./justfile")
        self.assertNotEqual(code, 0)

    def test_3_two_arguments_success(self):
        code, _, _ = run_command("./copy ./justfile ./demo")
        self.assertEqual(code, 0)
        self.assertTrue(os.path.isfile("./demo/justfile"))

    def test_4_illegal_destination(self):
        code, _, _ = run_command("./copy ./justfile ./copy")
        self.assertNotEqual(code, 0)

    def test_5_illegal_source(self):
        code, _, _ = run_command("./copy ./not_exist ./demo")
        self.assertNotEqual(code, 0)

    def test_6_copy_file_to_itself(self):
        run_command("touch ./demo/justfile")
        code, _, _ = run_command("./copy ./demo/justfile ./demo")
        self.assertNotEqual(code, 0)

    def test_7_overwrite_prompt(self):
        run_command("touch ./demo/justfile")
        code, _, _ = run_command("./copy ./justfile ./demo")
        self.assertEqual(code, 0)
        self.assertTrue(os.path.isfile("./demo/justfile"))

    def test_8_move_two_files(self):
        run_command("touch demo1.txt && touch demo2.txt")
        code, _, _ = run_command("./move ./demo1.txt ./demo2.txt ./demo")
        self.assertEqual(code, 0)

    def test_9_failed_move(self):
        code, _, _ = run_command("./move /etc/passwd ./demo")
        self.assertNotEqual(code, 0)


if __name__ == "__main__":
    unittest.main()

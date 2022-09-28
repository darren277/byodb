
import subprocess

def test_main():
    p = subprocess.Popen(['./main', 'mydb.db'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = p.communicate(b'insert foo bar\n')
    p.stdin.close()
    assert out.splitlines()[0].rstrip() == 'db > This is where we would do an insert.'

test_main()
print('All tests passed!')

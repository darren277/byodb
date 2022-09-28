
import subprocess
import pexpect
from pexpect import popen_spawn

def test_main():
    p = subprocess.Popen(['./main', 'mydb.db'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = p.communicate(b'insert foo bar\n')
    p.stdin.close()
    assert out.splitlines()[0].rstrip() == 'db > This is where we would do an insert.'

def test_insert_and_select():
    p = subprocess.Popen(['./main', 'mydb.db'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    p.stdin.write(b'insert 1 cstack foo@bar.com\n')
    print('1')
    p.stdin.flush()
    p.stdin.write(b'select\n')
    print('2')
    p.stdin.flush()
    p.stdin.write(b'insert foo bar 1\n')
    print('3')
    p.stdin.flush()
    p.stdin.write(b'.exit\n')
    out = p.stdout.readlines()
    assert out[0].rstrip() == 'db > Executed.'
    assert out[1].rstrip() == 'db > (1, cstack, foo@bar.com)'
    assert out[3].rstrip() == 'db > Syntax error. Could not parse statement.'


#test_main()
test_insert_and_select()
print('All tests passed!')

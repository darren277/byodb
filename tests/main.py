
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
    print(out)
    assert out[0].rstrip() == 'db > Executed.'
    assert out[1].rstrip() == 'db > (1, cstack, foo@bar.com)'
    assert out[3].rstrip() == 'db > Syntax error. Could not parse statement.'


def test_max_string_length():
    long_username = "a"*32
    long_email = "a"*255
    print(long_username)

    p = subprocess.Popen(['./main', 'mydb.db'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    p.stdin.write(b'insert 1 {} {}\n'.format(long_username, long_email))
    p.stdin.flush()
    p.stdin.write(b'select\n')
    p.stdin.flush()
    p.stdin.write(b'.exit\n')
    out = p.stdout.readlines()
    print(out)
    assert out[1].rstrip() == 'db > (1, {}, {})'.format(long_username, long_email)

    long_username = "a"*33
    long_email = "a"*255
    print(long_username)

    p = subprocess.Popen(['./main', 'mydb.db'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    p.stdin.write(b'insert 1 {} {}\n'.format(long_username, long_email))
    p.stdin.flush()
    p.stdin.write(b'select\n')
    p.stdin.flush()
    p.stdin.write(b'.exit\n')
    out = p.stdout.readlines()
    print(out)
    assert out[0].rstrip() == 'db > String is too long.'


def test_table_full():
    p = subprocess.Popen(['./main', 'mydb.db'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    for i in range(1400):
        p.stdin.write(b'insert 1 cstack user@user.com\n')
        p.stdin.flush()
    p.stdin.write(b'.exit\n')
    out = p.stdout.readlines()
    print(out)
    assert not any([x for x in out if 'Error: Table full' in x])

    p = subprocess.Popen(['./main', 'mydb.db'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    for i in range(1401):
        p.stdin.write(b'insert 1 cstack user@user.com\n')
        p.stdin.flush()
    p.stdin.write(b'.exit\n')
    out = p.stdout.readlines()
    print(out)
    assert any([x for x in out if 'Error: Table full' in x])


#test_main()
test_insert_and_select()
#test_table_full()

test_max_string_length()

print('All tests passed!')

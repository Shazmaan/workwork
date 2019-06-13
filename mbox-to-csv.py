import mailbox
import unicodecsv
import os
import subprocess

def unicodetoascii(text):

    uni2ascii = {
            ord('\xe2\x80\x99'.decode('utf-8')): ord("'"),
            ord('\xe2\x80\x9c'.decode('utf-8')): ord('"'),
            ord('\xe2\x80\x9d'.decode('utf-8')): ord('"'),
            ord('\xe2\x80\x9e'.decode('utf-8')): ord('"'),
            ord('\xe2\x80\x9f'.decode('utf-8')): ord('"'),
            ord('\xc3\xa9'.decode('utf-8')): ord('e'),
            ord('\xe2\x80\x9c'.decode('utf-8')): ord('"'),
            ord('\xe2\x80\x93'.decode('utf-8')): ord('-'),
            ord('\xe2\x80\x92'.decode('utf-8')): ord('-'),
            ord('\xe2\x80\x94'.decode('utf-8')): ord('-'),
            ord('\xe2\x80\x94'.decode('utf-8')): ord('-'),
            ord('\xe2\x80\x98'.decode('utf-8')): ord("'"),
            ord('\xe2\x80\x9b'.decode('utf-8')): ord("'"),

            ord('\xe2\x80\x90'.decode('utf-8')): ord('-'),
            ord('\xe2\x80\x91'.decode('utf-8')): ord('-'),

            ord('\xe2\x80\xb2'.decode('utf-8')): ord("'"),
            ord('\xe2\x80\xb3'.decode('utf-8')): ord("'"),
            ord('\xe2\x80\xb4'.decode('utf-8')): ord("'"),
            ord('\xe2\x80\xb5'.decode('utf-8')): ord("'"),
            ord('\xe2\x80\xb6'.decode('utf-8')): ord("'"),
            ord('\xe2\x80\xb7'.decode('utf-8')): ord("'"),

            ord('\xe2\x81\xba'.decode('utf-8')): ord("+"),
            ord('\xe2\x81\xbb'.decode('utf-8')): ord("-"),
            ord('\xe2\x81\xbc'.decode('utf-8')): ord("="),
            ord('\xe2\x81\xbd'.decode('utf-8')): ord("("),
            ord('\xe2\x81\xbe'.decode('utf-8')): ord(")"),

                            }
    return text.decode('utf-8').translate(uni2ascii).encode('ascii')

csvfile = open("mbox-output.csv", "wb+")
writer = unicodecsv.writer(csvfile,encoding="utf-8")
writer.writerow(["Parent","Girl","Message-ID","Subject","Reply-To","Good Email","Phone Number","Secondary Contact","Phone Number(2)","allergies or medical/emotional issues?","Anything else we should know about?","Date"])

checkArray={}
girlArray={}
girlList=[]
for message in mailbox.mbox('Registered Users.mbox'):
        if message.is_multipart():
            content = ''.join(part.get_payload(decode=True) for part in message.get_payload())
        else:
            content = message.get_payload(decode=True)
            array=content.split('\n')
            if (array[0][0:12]!="Week of Camp"):
                    Parent=array[0].split(':')
                    Girl=array[1].split(':')
                    good_email=array[2].split(':')
                    if(unicodetoascii(Girl[1].strip().lower()) in girlList):
                            continue
                    else:
                            girlList.append(unicodetoascii(Girl[1].strip().lower()))
                    girlArray[unicodetoascii(Girl[1].strip().lower())]=unicodetoascii(Parent[1].strip().lower())
                    checkArray[unicodetoascii(Parent[1].strip().lower())]=[[unicodetoascii(Girl[1].strip()),message['message-id'], message['subject'],message['Reply-To'],good_email[1].strip(),array[3][7:],unicodetoascii(array[4][19:]),array[5][9:],unicodetoascii(array[6][39:]),unicodetoascii(array[7][37:]),message['date']]]
            else:
                    continue
listofTuples = sorted(girlArray.items() ,  key=lambda x: x[1])
for x in listofTuples:
        A=x[1]
        B=checkArray[x[1]][0][0]
        C=checkArray[x[1]][0][1]
        D=checkArray[x[1]][0][2]
        E=checkArray[x[1]][0][3]
        F=checkArray[x[1]][0][4]
        G=checkArray[x[1]][0][5]
        H=checkArray[x[1]][0][6]
        I=checkArray[x[1]][0][7]
        J=checkArray[x[1]][0][8]
        K=checkArray[x[1]][0][9]
        L=checkArray[x[1]][0][10]
        writer.writerow([A,B,C,D,E,F,G,H,I,J,K,L])
csvfile.close()

string=os.path.realpath(__file__)
length=len(string)
location=string[:(length-14)]

cmd = location+"workwork.exe"
process = subprocess.Popen(cmd, stdout=subprocess.PIPE, creationflags=0x08000000)
process.wait()

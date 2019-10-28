import time,Manu

def get_gps(arg,exp):
    Protocol_gpstime.Hour.Value=arg[0]
    Protocol_gpstime.Minute.Value=arg[1]
    Protocol_gpstime.Second.Value=arg[2]
    Protocol_gpstime.JingDu.Value=arg[3]
    Protocol_gpstime.Flag_JD.Value=arg[4]
    Protocol_gpstime.WeiDu.Value=arg[5]
    Protocol_gpstime.Flag_WD.Value=arg[6]
    Protocol_gpstime.Write()
    
def Test(arg,exp):    
    seekresult=CH_232_1.Clear()
    t1=time.time()
    t2=time.time()
    get_gps(arg,exp)
    while t2-t1<3:
          Protocol_ServerOutput.BlockRead()
          t2=time.time()
          if Protocol_ServerOutput.Flag.Value==1:
                break
    print "Ê±¼ä¼ä¸ô£º %d"%(t2-t1)

              
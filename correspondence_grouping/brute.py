#
#!/usr/bin/env
import os
import threading
import itertools
import numpy as np
import subprocess
import time
import json

class BashThread(threading.Thread):
  def __init__(self, cmd, row):
    self.cmd = cmd
    self.row = row
    threading.Thread.__init__(self)

  def run(self):
    msf = msk = stp = ssk = cf = mif = 0
    time_start = time.time()
    process = subprocess.Popen(self.cmd, shell=True, stdout=subprocess.PIPE)
    output = process.communicate()[0]
    while process.poll() is None:
      r = process.stdout.readline()
      if msfs in r:
        msf = float(r.replace(msfs, ''))
      elif msks in r:
        msk = float(r.replace(msks, ''))
      elif stps in r:
        stp = float(r.replace(stps, ''))
      elif ssks in r:
        ssk = float(r.replace(ssks, ''))
      elif cf in r:
        cf = float(r.replace(cf, ''))
      elif msks in r:
        mif = float(r.replace(mif, ''))

    time_end = time.time() - time_start
    self.row += 'msf:'+str(msf)+','+'msk:'+str(msk)+','+'stp:'+str(stp)+','+'ssk:'+str(ssk)+','+'cf:'+str(cf)+','+'mif:'+str(mif)+','+'time:'+str(time_end)

    f = open('brute_output.txt','a')

    f.write(self.row)
    f.close()

threadscount = 5

path = '.'

cmd =  './build/CorresponseGrouping ./data/scene.pcd ./data/newmodel.pcd '

msfs =  model_instances_found_s     = 'Model total points: '
msks = model_selected_keypoints_s   = 'Model Selected Keypoint: '
stps = scene_total_points_s         = 'Scene total points: '
ssks = scene_selected_keypoint_s    = 'Scene Selected Keypoint: '

cf  = corresponces_found            = 'Correspondences found: '
mif = model_instances_found         = 'Model instances found: '

model_ss_s  = '--model_ss {} '
scene_ss_s  = '--scene_ss {} '
rf_rad_s    = '--rf_rad {} '
descr_rad_s = '--descr_rad {} '
cg_size_s   = '--cg_size {} '
cg_thresh_s = '--cg_thres {}'

model_ss    = scene_ss    = 0.01
rf_rad      = 0.015
descr_rad   = 0.02
cg_size     = 0.01
cg_thresh   = 5.0

ss_range = np.arange(0.005, 0.05, 0.005)
rf_rad_range      = np.arange(0.010, 1.020, 0.005)
descr_rad_range = np.arange(0.01, 0.04, 0.005)
cg_size_range = np.arange(0.005, 0.03, 0.005)
cg_thresh_range = np.arange(4, 6, 0.5)

i = 0

for ss, rf_rad, descr_rad, cg_size, cg_thresh in itertools.product(
    ss_range, rf_rad_range, descr_rad_range, cg_size_range, cg_thresh_range):
    i += 1

total_iterations = i

i = 0

f = open('brute_output.txt','w')
f.write(cmd + '\n')
f.close()

for ss, rf_rad, descr_rad, cg_size, cg_thresh in itertools.product(
    ss_range, rf_rad_range, descr_rad_range, cg_size_range, cg_thresh_range):
    while True:

      if threading.activeCount() != threadscount:
        try:

          i += 1

          if i % 100 == 0:
            print 'iteration '+str(i)+ ' of ', total_iterations

          row =  'ss:'+str(ss)+','+'rf_rad:'+str(rf_rad)+','+'descr_rad:'+str(descr_rad)+','+'cg_size:'+str(cg_size)+','+'cg_thresh:'+str(cg_thresh)+','
          cmd_formatted = cmd + model_ss_s.format(str(ss)) +(
           scene_ss_s.format(str(ss)) + rf_rad_s.format(str(rf_rad)) +(
           descr_rad_s.format(str(descr_rad)) + cg_size_s.format(str(cg_size)) +(
           cg_thresh_s.format(str(cg_thresh)))))
          BashThread(cmd_formatted, row).start()

          break
        except Exception, e:
          print 'error at:', row
        break

    # break

print 'end'


def main():
    pass

if __name__ == '__main__':
    main()

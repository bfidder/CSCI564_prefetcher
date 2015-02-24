#include "prefetcher.h"
#include "mem-sim.h"
#include <stdio.h>

Prefetcher::Prefetcher() {
  for (int i = 0; i < N; ++i) {
    _readys[i] = false;
  }
  // _ready = false;
}

bool Prefetcher::hasRequest(u_int32_t cycle) {
  bool all = false;
  for (int i = 0; i < N; ++i) {
    all |= _readys[i];
  }
  return all;
	// return _ready;
}

Request Prefetcher::getRequest(u_int32_t cycle) {
  Request r = _nextReq;
  for (int i = 0; i < N; ++i) {
    r.addr += 16;
    if(_readys[i]) {
      break;
    }
  }
	return r;
  // _nextReq.addr += 16;
  // return _nextReq;
}

void Prefetcher::completeRequest(u_int32_t cycle) { 
  for (int i = 0; i < N; ++i) {
    if(_readys[i]) {
      _readys[i] = false;
      break;
    }
    // _readys[i] = false;
  }
  // _ready = false; 
}

void Prefetcher::cpuRequest(Request req) {
  printf("%u\t%i\n", req.addr, req.HitL1);
  bool ready = !req.HitL1;
  for (int i = 0; i < N; ++i) {
    ready &= !_readys[i];
  }

  if(ready) {
		_nextReq.addr = req.addr;
    for (int i = 0; i < N; ++i) {
      _readys[i] = true;
    }
		// _ready = true;
	}
}

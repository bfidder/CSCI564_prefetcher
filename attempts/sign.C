#include "prefetcher.h"
#include "mem-sim.h"
#include <stdio.h>

Prefetcher::Prefetcher() {
  last_addr_1 = 0;
  last_addr_2 = 0;
  sign = 1;
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
    if(_readys[i]) {
      r.addr += sign*16;
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
  last_addr_2 = last_addr_1;
  last_addr_1 = req.addr;
  sign = last_addr_1 >= last_addr_2 ? 1 : -1;
  printf("%u\t%i\t%u - %u = %i\n", req.addr, req.HitL1, last_addr_1, last_addr_2, sign);
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

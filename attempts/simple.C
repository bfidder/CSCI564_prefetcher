#include "prefetcher.h"
#include "mem-sim.h"
#include <stdio.h>

Prefetcher::Prefetcher() {_ready = false;}

bool Prefetcher::hasRequest(u_int32_t cycle) {
	return _ready;
}

Request Prefetcher::getRequest(u_int32_t cycle) {
	return _nextReq;
}

void Prefetcher::completeRequest(u_int32_t cycle) { 
  _ready = false; 
}

void Prefetcher::cpuRequest(Request req) {
  printf("%u\t%i\n", req.addr, req.HitL1);
  if(!_ready && !req.HitL1) {
		_nextReq.addr = req.addr + 16;
		_ready = true;
	}
}

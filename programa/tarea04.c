/*
 * Copyright (C) 2010
 * Pablo Alvarado
 *
 * This file is part of the EL-5805 Digital Signal Processing Lecture at
 * the Costa Rica Institute of Technology
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the authors nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** 
 * \file   tarea04.c
 *         Contains the processing function
 * \author Pablo Alvarado
 * \author Student
 * \date   August 9th, 2010
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#define DELAY_MS 500.0
#define ALPHA 0.2
/**
 * You may need some global values 
 */
float * feedback_buffer;
float * out_buffer;
uint32_t k;
uint32_t l_f;
uint32_t k_f;
/**
 * This method is called before the real processing starts.
 * You may use it to initialize whatever you need to.
 */
void init(const unsigned int Fs) {
    
  k = (uint32_t)((float)Fs * DELAY_MS/1000);
  l_f = k/1024 + 1;
  k_f = l_f * 1024;
 
  feedback_buffer = malloc(sizeof(float)*k_f);
  memset(feedback_buffer,0,sizeof(float)*k_f);

  out_buffer = malloc(sizeof(float)*k_f);
  memset(out_buffer,0,sizeof(float)*k_f);
}

/**
 * Process a buffer of data.
 *
 * @param Fs sampling rate
 * @param channels number of channels per frame
 * @param frames   number of frames per buffer
 * @param buffer   input and output buffer
 *
 * @return zero if error, or 1 otherwise.
 */
int process(const unsigned int Fs,
            const int nframes,
            const float* in,
            float* out) {
  /*
   * PUT YOUR CODE IN HERE
   */
  static int nbatch = 0;

  for(int i; i<nframes;i++){
    out_buffer[i+nbatch*nframes] = (1-ALPHA)*in[i]+ALPHA*feedback_buffer[i+nbatch*nframes];  
  }
    
  /* This line just copies the data from input to output. REMOVE IT! */
  memcpy(out, out_buffer+(nbatch*nframes)/*in*/, sizeof(float)*nframes);
  /* Debug stuff */
  if (nbatch == l_f){
    nbatch = 0;
    memcpy(feedback_buffer, feedback_buffer+k,sizeof(float)*(k_f-k));
    memcpy(feedback_buffer+(k_f-k), out_buffer,sizeof(float)*k);
  }
  
  else nbatch ++;
    
  fflush(stdout);
  
  return 0; // everything is ok 
}


/*
 * Copyright (C) 2019 ETH Zurich, University of Bologna
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
* @Author: Alfio Di Mauro
* @Date:   2020-03-23 09:33:29
* @Last Modified by:   Alfio Di Mauro
* @Last Modified time: 2020-10-21 09:29:07
*/

#include "pulp.h"

#define DEBUG

static void spim_wait_tx_done(int periph)
{
	
 //#ifdef DEBUG
 //int periph_id = periph - ARCHI_UDMA_SPIM_ID(0);
 //  printf("periph_id = %d\n", periph_id);
 //#endif

  while (plp_udma_busy(UDMA_SPIM_TX_ADDR(periph - ARCHI_UDMA_UART_ID(0))))
  {
  }

  while(plp_uart_tx_busy(periph - ARCHI_UDMA_UART_ID(0)));
}


static void spim_wait_rx_done(int periph)
{
  while (plp_udma_busy(UDMA_UART_RX_ADDR(periph - ARCHI_UDMA_UART_ID(0))))
  {
  }
}

int qspi_write_nb(int qspi_id, void *buffer, uint32_t size)
{
  int periph_id = ARCHI_UDMA_SPIM_ID(qspi_id);
  int channel = UDMA_CHANNEL_ID(periph_id) + 1;

  unsigned int base = hal_udma_channel_base(channel);

  plp_udma_enqueue(base, (int)buffer, size, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_8);

  //uart_wait_tx_done(periph_id);

  return 0;
}

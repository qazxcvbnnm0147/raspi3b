# raspi3b - Raspberry Pi 3B 自訂啟動與內核配置

## 簡介
這個專案的目的是在 **Raspberry Pi 3B** 上實現一個自訂的啟動過程和內核配置。專案中涵蓋了 **bootloader** 設定、**Linux 內核** 的配置、自訂啟動選項，並實現了 **根檔案系統** 和其他嵌入式系統相關功能。它能夠展示如何從硬體層面開始設置一個嵌入式系統並將其運行起來。

## 主要功能
- **自訂啟動過程**：修改 **Raspberry Pi 3B** 的啟動流程，從 **bootloader** 到內核的加載與啟動。
- **內核與硬體配置**：自訂 **Linux 內核**，並根據需求進行修改與調整，支持與 **Raspberry Pi 3B** 硬體接口（如 GPIO）進行交互。
- **裝置樹 (Device Tree)** 配置：設定硬體設備並讓內核識別並適應這些設備。
- **根檔案系統管理**：管理與設定根檔案系統，確保系統能夠正確加載並運行。
- **硬體驅動程式支持**：實現對硬體設備（如 GPIO、UART 等）的驅動支持。

## 使用的技術
- **Raspberry Pi 3B**：嵌入式開發平台。
- **Linux 內核**：基於 **Linux** 內核進行自訂與配置。
- **C/C++**：用於編寫內核模組與驅動程式的編程語言。
- **Makefile**：用於管理專案的編譯過程。
- 
## 模擬環境
  透過**QEMU**模擬實際燒錄時的情況,並可透過**GDB**進行debug,以下是模擬時的命令:
  - qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial null -serial stdio -display none -dtb bcm2710-rpi-3-b-plus.dtb -initrd initramfs.cpio

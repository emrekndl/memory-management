**C’de Bellek Yönetimi**

Bu depo, bellek yönetiminin temellerini öğrenmek için adım adım C dilinde uygulamalar ve örnekler içeren bir eğitim serisini barındırır. Otomatik bellek yönetimi kullanan yüksek seviye dillerin aksine, bu seride _kendi çöp toplama algoritmalarınızı_ (refcounting ve mark-and-sweep) sıfırdan C ile nasıl inşa edeceğiniz gösterilmektedir.

> Eğitim içeriği boot.dev sitesindeki "Memory Management in C" (TJ DeVries) kursu temel alınarak derlenmiştir.

## Bölümler

1. **C Temelleri** (`1-basics/`)

    * C programlama dilinin temelleri.
2. **Struct’lar** (`2-structs/`)

    * Struct tanımlama ve bellek yerleşimi.
3. **Göstericiler (Pointers)** (`3-pointers/`)

    * Göstericilerle uygulamalı alıştırmalar.
4. **Enums** (`4-enums/`)

    * İsimlendirilmiş sabit kümeleri oluşturmak için enum kullanımı.
5. **Unions** (`5-unions/`)

    * C’de union veri yapısı ve TypeScript’ten farkları.
6. **Yığın ve Heap** (`6-stack-heap/`)

    * Yığın (stack) ve heap tahsis farkları.
7. **Gelişmiş Göstericiler** (`7-adv-pointers/`)

    * İşaretçi üzerine işaretçi, gösterici aritmetiği vb.
8. **Yığın Veri Yapısı** (`8-stack-ds/`)

    * Struct ve göstericilerle yığın veri yapısı uyarlaması.
9. **Nesneler (Objects)** (`9-objects/`)

    * Basit bir nesne sistemi oluşturma.
10. **Referans Sayma Çöp Toplayıcı (Refcounting GC)** (`10-refcounting-gc/`)

    * Referans sayma çöp toplayıcı uygulaması.
11. **Mark-Sweep Çöp Toplayıcı** (`11-mark-sweep-gc/`)

    * Mark-Sweep çöptoplama algoritması ve referans sayma karşılaştırması.

Her bölümde ilgili `main.c` ve `exercise*.c` dosyaları ile alıştırmalar yer alır.

## Gereksinimler

- GCC veya Clang (C99 desteği)
- Make
- [`munit`](https://github.com/nemequ/munit) – Basit bir C birim test kütüphanesi

## Kurulum

1. Depoyu klonlayın:

   ```bash
   git clone https://github.com/emrekndl/memory-management.git
   cd memory-management
   ```

2. `munit` alt modülünü ekleyin:

   ```bash
   git submodule add https://github.com/nemequ/munit.git munit
   git submodule update --init --recursive
   ```

3. (İsteğe bağlı) `munit` kütüphanesini derleyip kurun:

   ```bash
   cd munit
   meson setup builddir && meson compile -C builddir
   sudo meson install -C builddir
   ```

## Derleme ve Çalıştırma

Her bölümü klasör adıyla doğrudan derleyebilirsiniz:

### Kullanım

```bash
# Tüm bölümleri derlemek
make

# Sadece 1-basics bölümünü derlemek
make build 1-basics
# veya doğrudan klasör adıyla derlemek
make 1-basics

# 1-basics bölümünü derleyip çalıştırmak
make run 1-basics

# gcc yerine clang ile derlemek
env CC=clang make build 2-structs
```

Derlenen ikililer `bin/` klasöründe oluşturulur.

/****************************************************************************
 * arch/loongarch/include/csr.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/* This file should never be included directly but, rather, only indirectly
 * through nuttx/irq.h
 */

#ifndef __ARCH_LOONGARCH_INCLUDE_CSR_H
#define __ARCH_LOONGARCH_INCLUDE_CSR_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Basic CSR registers */
#define LOONGARCH_CSR_CRMD		0x0	/* Current mode info */
#define  CSR_CRMD_WE_SHIFT		9
#define  CSR_CRMD_WE			(UINT64_C(0x1) << CSR_CRMD_WE_SHIFT)
#define  CSR_CRMD_DATM_SHIFT		7
#define  CSR_CRMD_DATM_WIDTH		2
#define  CSR_CRMD_DATM			(UINT64_C(0x3) << CSR_CRMD_DATM_SHIFT)
#define  CSR_CRMD_DATF_SHIFT		5
#define  CSR_CRMD_DATF_WIDTH		2
#define  CSR_CRMD_DATF			(UINT64_C(0x3) << CSR_CRMD_DATF_SHIFT)
#define  CSR_CRMD_PG_SHIFT		4
#define  CSR_CRMD_PG			(UINT64_C(0x1) << CSR_CRMD_PG_SHIFT)
#define  CSR_CRMD_DA_SHIFT		3
#define  CSR_CRMD_DA			(UINT64_C(0x1) << CSR_CRMD_DA_SHIFT)
#define  CSR_CRMD_IE_SHIFT		2
#define  CSR_CRMD_IE			(0x1 << CSR_CRMD_IE_SHIFT)
#define  CSR_CRMD_PLV_SHIFT		0
#define  CSR_CRMD_PLV_WIDTH		2
#define  CSR_CRMD_PLV			(UINT64_C(0x3) << CSR_CRMD_PLV_SHIFT)

#define PLV_KERN			0
#define PLV_USER			3
#define PLV_MASK			0x3

#define LOONGARCH_CSR_PRMD		0x1	/* Prev-exception mode info */
#define  CSR_PRMD_PWE_SHIFT		3
#define  CSR_PRMD_PWE			(UINT64_C(0x1) << CSR_PRMD_PWE_SHIFT)
#define  CSR_PRMD_PIE_SHIFT		2
#define  CSR_PRMD_PIE			((0x1) << CSR_PRMD_PIE_SHIFT)
#define  CSR_PRMD_PPLV_SHIFT		0
#define  CSR_PRMD_PPLV_WIDTH		2
#define  CSR_PRMD_PPLV			((0x3) << CSR_PRMD_PPLV_SHIFT)

#define LOONGARCH_CSR_EUEN		0x2	/* Extended unit enable */
#define  CSR_EUEN_LBTEN_SHIFT		3
#define  CSR_EUEN_LBTEN			(UINT64_C(0x1) << CSR_EUEN_LBTEN_SHIFT)
#define  CSR_EUEN_LASXEN_SHIFT		2
#define  CSR_EUEN_LASXEN		(UINT64_C(0x1) << CSR_EUEN_LASXEN_SHIFT)
#define  CSR_EUEN_LSXEN_SHIFT		1
#define  CSR_EUEN_LSXEN			(UINT64_C(0x1) << CSR_EUEN_LSXEN_SHIFT)
#define  CSR_EUEN_FPEN_SHIFT		0
#define  CSR_EUEN_FPEN			(UINT64_C(0x1) << CSR_EUEN_FPEN_SHIFT)

#define LOONGARCH_CSR_MISC		0x3	/* Misc config */

#define LOONGARCH_CSR_ECFG		0x4	/* Exception config */
#define  CSR_ECFG_VS_SHIFT		16
#define  CSR_ECFG_VS_WIDTH		3
#define  CSR_ECFG_VS			(UINT64_C(0x7) << CSR_ECFG_VS_SHIFT)
#define  CSR_ECFG_IM_SHIFT		0
#define  CSR_ECFG_IM_WIDTH		13
#define  CSR_ECFG_IM			(UINT64_C(0x1fff) << CSR_ECFG_IM_SHIFT)

#define LOONGARCH_CSR_ESTAT		0x5	/* Exception status */
#define  CSR_ESTAT_ESUBCODE_SHIFT	22
#define  CSR_ESTAT_ESUBCODE_WIDTH	9
#define  CSR_ESTAT_ESUBCODE		(UINT64_C(0x1ff) << CSR_ESTAT_ESUBCODE_SHIFT)
#define  CSR_ESTAT_EXC_SHIFT		16
#define  CSR_ESTAT_EXC_WIDTH		6
#define  CSR_ESTAT_EXC			(UINT64_C(0x3f) << CSR_ESTAT_EXC_SHIFT)
#define  CSR_ESTAT_IS_SHIFT		0
#define  CSR_ESTAT_IS_WIDTH		15
#define  CSR_ESTAT_IS			(UINT64_C(0x7fff) << CSR_ESTAT_IS_SHIFT)

#define LOONGARCH_CSR_ERA		0x6	/* ERA */

#define LOONGARCH_CSR_BADV		0x7	/* Bad virtual address */

#define LOONGARCH_CSR_BADI		0x8	/* Bad instruction */

#define LOONGARCH_CSR_EENTRY		0xc	/* Exception entry */

/* TLB related CSR registers */
#define LOONGARCH_CSR_TLBIDX		0x10	/* TLB Index, EHINV, PageSize, NP */
#define  CSR_TLBIDX_EHINV_SHIFT		31
#define  CSR_TLBIDX_EHINV		(UINT64_C(1) << CSR_TLBIDX_EHINV_SHIFT)
#define  CSR_TLBIDX_PS_SHIFT		24
#define  CSR_TLBIDX_PS_WIDTH		6
#define  CSR_TLBIDX_PS			(UINT64_C(0x3f) << CSR_TLBIDX_PS_SHIFT)
#define  CSR_TLBIDX_IDX_SHIFT		0
#define  CSR_TLBIDX_IDX_WIDTH		12
#define  CSR_TLBIDX_IDX			(UINT64_C(0xfff) << CSR_TLBIDX_IDX_SHIFT)
#define  CSR_TLBIDX_SIZEM		0x3f000000
#define  CSR_TLBIDX_SIZE		CSR_TLBIDX_PS_SHIFT
#define  CSR_TLBIDX_IDXM		0xfff
#define  CSR_INVALID_ENTRY(e)		(CSR_TLBIDX_EHINV | e)

#define LOONGARCH_CSR_TLBEHI		0x11	/* TLB EntryHi */

#define LOONGARCH_CSR_TLBELO0		0x12	/* TLB EntryLo0 */
#define  CSR_TLBLO0_RPLV_SHIFT		63
#define  CSR_TLBLO0_RPLV		(UINT64_C(0x1) << CSR_TLBLO0_RPLV_SHIFT)
#define  CSR_TLBLO0_NX_SHIFT		62
#define  CSR_TLBLO0_NX			(UINT64_C(0x1) << CSR_TLBLO0_NX_SHIFT)
#define  CSR_TLBLO0_NR_SHIFT		61
#define  CSR_TLBLO0_NR			(UINT64_C(0x1) << CSR_TLBLO0_NR_SHIFT)
#define  CSR_TLBLO0_PFN_SHIFT		12
#define  CSR_TLBLO0_PFN_WIDTH		36
#define  CSR_TLBLO0_PFN			(UINT64_C(0xfffffffff) << CSR_TLBLO0_PFN_SHIFT)
#define  CSR_TLBLO0_GLOBAL_SHIFT	6
#define  CSR_TLBLO0_GLOBAL		(UINT64_C(0x1) << CSR_TLBLO0_GLOBAL_SHIFT)
#define  CSR_TLBLO0_CCA_SHIFT		4
#define  CSR_TLBLO0_CCA_WIDTH		2
#define  CSR_TLBLO0_CCA			(UINT64_C(0x3) << CSR_TLBLO0_CCA_SHIFT)
#define  CSR_TLBLO0_PLV_SHIFT		2
#define  CSR_TLBLO0_PLV_WIDTH		2
#define  CSR_TLBLO0_PLV			(UINT64_C(0x3) << CSR_TLBLO0_PLV_SHIFT)
#define  CSR_TLBLO0_WE_SHIFT		1
#define  CSR_TLBLO0_WE			(UINT64_C(0x1) << CSR_TLBLO0_WE_SHIFT)
#define  CSR_TLBLO0_V_SHIFT		0
#define  CSR_TLBLO0_V			(UINT64_C(0x1) << CSR_TLBLO0_V_SHIFT)

#define LOONGARCH_CSR_TLBELO1		0x13	/* TLB EntryLo1 */
#define  CSR_TLBLO1_RPLV_SHIFT		63
#define  CSR_TLBLO1_RPLV		(UINT64_C(0x1) << CSR_TLBLO1_RPLV_SHIFT)
#define  CSR_TLBLO1_NX_SHIFT		62
#define  CSR_TLBLO1_NX			(UINT64_C(0x1) << CSR_TLBLO1_NX_SHIFT)
#define  CSR_TLBLO1_NR_SHIFT		61
#define  CSR_TLBLO1_NR			(UINT64_C(0x1) << CSR_TLBLO1_NR_SHIFT)
#define  CSR_TLBLO1_PFN_SHIFT		12
#define  CSR_TLBLO1_PFN_WIDTH		36
#define  CSR_TLBLO1_PFN			(UINT64_C(0xfffffffff) << CSR_TLBLO1_PFN_SHIFT)
#define  CSR_TLBLO1_GLOBAL_SHIFT	6
#define  CSR_TLBLO1_GLOBAL		(UINT64_C(0x1) << CSR_TLBLO1_GLOBAL_SHIFT)
#define  CSR_TLBLO1_CCA_SHIFT		4
#define  CSR_TLBLO1_CCA_WIDTH		2
#define  CSR_TLBLO1_CCA			(UINT64_C(0x3) << CSR_TLBLO1_CCA_SHIFT)
#define  CSR_TLBLO1_PLV_SHIFT		2
#define  CSR_TLBLO1_PLV_WIDTH		2
#define  CSR_TLBLO1_PLV			(UINT64_C(0x3) << CSR_TLBLO1_PLV_SHIFT)
#define  CSR_TLBLO1_WE_SHIFT		1
#define  CSR_TLBLO1_WE			(UINT64_C(0x1) << CSR_TLBLO1_WE_SHIFT)
#define  CSR_TLBLO1_V_SHIFT		0
#define  CSR_TLBLO1_V			(UINT64_C(0x1) << CSR_TLBLO1_V_SHIFT)

#define LOONGARCH_CSR_GTLBC		0x15	/* Guest TLB control */
#define  CSR_GTLBC_RID_SHIFT		16
#define  CSR_GTLBC_RID_WIDTH		8
#define  CSR_GTLBC_RID			(UINT64_C(0xff) << CSR_GTLBC_RID_SHIFT)
#define  CSR_GTLBC_TOTI_SHIFT		13
#define  CSR_GTLBC_TOTI			(UINT64_C(0x1) << CSR_GTLBC_TOTI_SHIFT)
#define  CSR_GTLBC_USERID_SHIFT		12
#define  CSR_GTLBC_USERID		(UINT64_C(0x1) << CSR_GTLBC_USERID_SHIFT)
#define  CSR_GTLBC_GMTLBSZ_SHIFT	0
#define  CSR_GTLBC_GMTLBSZ_WIDTH	6
#define  CSR_GTLBC_GMTLBSZ		(UINT64_C(0x3f) << CSR_GTLBC_GMTLBSZ_SHIFT)

#define LOONGARCH_CSR_TRGP		0x16	/* TLBR read guest info */
#define  CSR_TRGP_RID_SHIFT		16
#define  CSR_TRGP_RID_WIDTH		8
#define  CSR_TRGP_RID			(UINT64_C(0xff) << CSR_TRGP_RID_SHIFT)
#define  CSR_TRGP_GTLB_SHIFT		0
#define  CSR_TRGP_GTLB			(1 << CSR_TRGP_GTLB_SHIFT)

#define LOONGARCH_CSR_ASID		0x18	/* ASID */
#define  CSR_ASID_BIT_SHIFT		16	/* ASIDBits */
#define  CSR_ASID_BIT_WIDTH		8
#define  CSR_ASID_BIT			(UINT64_C(0xff) << CSR_ASID_BIT_SHIFT)
#define  CSR_ASID_ASID_SHIFT		0
#define  CSR_ASID_ASID_WIDTH		10
#define  CSR_ASID_ASID			(UINT64_C(0x3ff) << CSR_ASID_ASID_SHIFT)

#define LOONGARCH_CSR_PGDL		0x19	/* Page table base address when VA[47] = 0 */

#define LOONGARCH_CSR_PGDH		0x1a	/* Page table base address when VA[47] = 1 */

#define LOONGARCH_CSR_PGD		0x1b	/* Page table base */

#define LOONGARCH_CSR_PWCTL0		0x1c	/* PWCtl0 */
#define  CSR_PWCTL0_PTEW_SHIFT		30
#define  CSR_PWCTL0_PTEW_WIDTH		2
#define  CSR_PWCTL0_PTEW		(UINT64_C(0x3) << CSR_PWCTL0_PTEW_SHIFT)
#define  CSR_PWCTL0_DIR2WIDTH_SHIFT	25
#define  CSR_PWCTL0_DIR2WIDTH_WIDTH	5
#define  CSR_PWCTL0_DIR2WIDTH		(UINT64_C(0x1f) << CSR_PWCTL0_DIR1WIDTH_SHIFT)
#define  CSR_PWCTL0_DIR2BASE_SHIFT	20
#define  CSR_PWCTL0_DIR2BASE_WIDTH	5
#define  CSR_PWCTL0_DIR2BASE		(UINT64_C(0x1f) << CSR_PWCTL0_DIR1BASE_SHIFT)
#define  CSR_PWCTL0_DIR1WIDTH_SHIFT	15
#define  CSR_PWCTL0_DIR1WIDTH_WIDTH	5
#define  CSR_PWCTL0_DIR1WIDTH		(UINT64_C(0x1f) << CSR_PWCTL0_DIR0WIDTH_SHIFT)
#define  CSR_PWCTL0_DIR1BASE_SHIFT	10
#define  CSR_PWCTL0_DIR1BASE_WIDTH	5
#define  CSR_PWCTL0_DIR1BASE		(UINT64_C(0x1f) << CSR_PWCTL0_DIR0BASE_SHIFT)
#define  CSR_PWCTL0_PTWIDTH_SHIFT	5
#define  CSR_PWCTL0_PTWIDTH_WIDTH	5
#define  CSR_PWCTL0_PTWIDTH		(UINT64_C(0x1f) << CSR_PWCTL0_PTWIDTH_SHIFT)
#define  CSR_PWCTL0_PTBASE_SHIFT	0
#define  CSR_PWCTL0_PTBASE_WIDTH	5
#define  CSR_PWCTL0_PTBASE		(UINT64_C(0x1f) << CSR_PWCTL0_PTBASE_SHIFT)

#define LOONGARCH_CSR_PWCTL1		0x1d	/* PWCtl1 */
#define  CSR_PWCTL1_DIR4WIDTH_SHIFT	18
#define  CSR_PWCTL1_DIR4WIDTH_WIDTH	5
#define  CSR_PWCTL1_DIR4WIDTH		(UINT64_C(0x1f) << CSR_PWCTL1_DIR3WIDTH_SHIFT)
#define  CSR_PWCTL1_DIR4BASE_SHIFT	12
#define  CSR_PWCTL1_DIR4BASE_WIDTH	5
#define  CSR_PWCTL1_DIR4BASE		(UINT64_C(0x1f) << CSR_PWCTL0_DIR3BASE_SHIFT)
#define  CSR_PWCTL1_DIR3WIDTH_SHIFT	6
#define  CSR_PWCTL1_DIR3WIDTH_WIDTH	5
#define  CSR_PWCTL1_DIR3WIDTH		(UINT64_C(0x1f) << CSR_PWCTL1_DIR2WIDTH_SHIFT)
#define  CSR_PWCTL1_DIR3BASE_SHIFT	0
#define  CSR_PWCTL1_DIR3BASE_WIDTH	5
#define  CSR_PWCTL1_DIR3BASE		(UINT64_C(0x1f) << CSR_PWCTL0_DIR2BASE_SHIFT)

#define LOONGARCH_CSR_STLBPGSIZE	0x1e
#define  CSR_STLBPGSIZE_PS_WIDTH	6
#define  CSR_STLBPGSIZE_PS		(UINT64_C(0x3f))

#define LOONGARCH_CSR_RVACFG		0x1f
#define  CSR_RVACFG_RDVA_WIDTH		4
#define  CSR_RVACFG_RDVA		(UINT64_C(0xf))

/* Config CSR registers */
#define LOONGARCH_CSR_CPUID		0x20	/* CPU core id */
#define  CSR_CPUID_COREID_WIDTH		9
#define  CSR_CPUID_COREID		UINT64_C(0x1ff)

#define LOONGARCH_CSR_PRCFG1		0x21	/* Config1 */
#define  CSR_CONF1_VSMAX_SHIFT		12
#define  CSR_CONF1_VSMAX_WIDTH		3
#define  CSR_CONF1_VSMAX		(UINT64_C(7) << CSR_CONF1_VSMAX_SHIFT)
#define  CSR_CONF1_TMRBITS_SHIFT	4
#define  CSR_CONF1_TMRBITS_WIDTH	8
#define  CSR_CONF1_TMRBITS		(UINT64_C(0xff) << CSR_CONF1_TMRBITS_SHIFT)
#define  CSR_CONF1_KSNUM_WIDTH		4
#define  CSR_CONF1_KSNUM		UINT64_C(0xf)

#define LOONGARCH_CSR_PRCFG2		0x22	/* Config2 */
#define  CSR_CONF2_PGMASK_SUPP		0x3ffff000

#define LOONGARCH_CSR_PRCFG3		0x23	/* Config3 */
#define  CSR_CONF3_STLBIDX_SHIFT	20
#define  CSR_CONF3_STLBIDX_WIDTH	6
#define  CSR_CONF3_STLBIDX		(UINT64_C(0x3f) << CSR_CONF3_STLBIDX_SHIFT)
#define  CSR_CONF3_STLBWAYS_SHIFT	12
#define  CSR_CONF3_STLBWAYS_WIDTH	8
#define  CSR_CONF3_STLBWAYS		(UINT64_C(0xff) << CSR_CONF3_STLBWAYS_SHIFT)
#define  CSR_CONF3_MTLBSIZE_SHIFT	4
#define  CSR_CONF3_MTLBSIZE_WIDTH	8
#define  CSR_CONF3_MTLBSIZE		(UINT64_C(0xff) << CSR_CONF3_MTLBSIZE_SHIFT)
#define  CSR_CONF3_TLBTYPE_SHIFT	0
#define  CSR_CONF3_TLBTYPE_WIDTH	4
#define  CSR_CONF3_TLBTYPE		(UINT64_C(0xf) << CSR_CONF3_TLBTYPE_SHIFT)

/* Kscratch registers */
#define LOONGARCH_CSR_KS0		0x30
#define LOONGARCH_CSR_KS1		0x31
#define LOONGARCH_CSR_KS2		0x32
#define LOONGARCH_CSR_KS3		0x33
#define LOONGARCH_CSR_KS4		0x34
#define LOONGARCH_CSR_KS5		0x35
#define LOONGARCH_CSR_KS6		0x36
#define LOONGARCH_CSR_KS7		0x37
#define LOONGARCH_CSR_KS8		0x38

/* Exception allocated KS0, KS1 and KS2 statically */
#define EXCEPTION_KS0			LOONGARCH_CSR_KS0
#define EXCEPTION_KS1			LOONGARCH_CSR_KS1
#define EXCEPTION_KS2			LOONGARCH_CSR_KS2
#define EXC_KSCRATCH_MASK		(1 << 0 | 1 << 1 | 1 << 2)

/* Percpu-data base allocated KS3 statically */
#define PERCPU_BASE_KS			LOONGARCH_CSR_KS3
#define PERCPU_KSCRATCH_MASK		(1 << 3)

/* KVM allocated KS4 and KS5 statically */
#define KVM_VCPU_KS			LOONGARCH_CSR_KS4
#define KVM_TEMP_KS			LOONGARCH_CSR_KS5
#define KVM_KSCRATCH_MASK		(1 << 4 | 1 << 5)

/* Timer registers */
#define LOONGARCH_CSR_TMID		0x40	/* Timer ID */

#define LOONGARCH_CSR_TCFG		0x41	/* Timer config */
#define  CSR_TCFG_VAL_SHIFT		2
#define	 CSR_TCFG_VAL_WIDTH		48
#define  CSR_TCFG_VAL			(UINT64_C(0x3fffffffffff) << CSR_TCFG_VAL_SHIFT)
#define  CSR_TCFG_PERIOD_SHIFT		1
#define  CSR_TCFG_PERIOD		(UINT64_C(0x1) << CSR_TCFG_PERIOD_SHIFT)
#define  CSR_TCFG_EN			(UINT64_C(0x1))

#define LOONGARCH_CSR_TVAL		0x42	/* Timer value */

#define LOONGARCH_CSR_CNTC		0x43	/* Timer offset */

#define LOONGARCH_CSR_TINTCLR		0x44	/* Timer interrupt clear */
#define  CSR_TINTCLR_TI_SHIFT		0
#define  CSR_TINTCLR_TI			(1 << CSR_TINTCLR_TI_SHIFT)

/* Guest registers */
#define LOONGARCH_CSR_GSTAT		0x50	/* Guest status */
#define  CSR_GSTAT_GID_SHIFT		16
#define  CSR_GSTAT_GID_WIDTH		8
#define  CSR_GSTAT_GID			(UINT64_C(0xff) << CSR_GSTAT_GID_SHIFT)
#define  CSR_GSTAT_GIDBIT_SHIFT		4
#define  CSR_GSTAT_GIDBIT_WIDTH		6
#define  CSR_GSTAT_GIDBIT		(UINT64_C(0x3f) << CSR_GSTAT_GIDBIT_SHIFT)
#define  CSR_GSTAT_PVM_SHIFT		1
#define  CSR_GSTAT_PVM			(UINT64_C(0x1) << CSR_GSTAT_PVM_SHIFT)
#define  CSR_GSTAT_VM_SHIFT		0
#define  CSR_GSTAT_VM			(UINT64_C(0x1) << CSR_GSTAT_VM_SHIFT)

#define LOONGARCH_CSR_GCFG		0x51	/* Guest config */
#define  CSR_GCFG_GPERF_SHIFT		24
#define  CSR_GCFG_GPERF_WIDTH		3
#define  CSR_GCFG_GPERF			(UINT64_C(0x7) << CSR_GCFG_GPERF_SHIFT)
#define  CSR_GCFG_GCI_SHIFT		20
#define  CSR_GCFG_GCI_WIDTH		2
#define  CSR_GCFG_GCI			(UINT64_C(0x3) << CSR_GCFG_GCI_SHIFT)
#define  CSR_GCFG_GCI_ALL		(UINT64_C(0x0) << CSR_GCFG_GCI_SHIFT)
#define  CSR_GCFG_GCI_HIT		(UINT64_C(0x1) << CSR_GCFG_GCI_SHIFT)
#define  CSR_GCFG_GCI_SECURE		(UINT64_C(0x2) << CSR_GCFG_GCI_SHIFT)
#define  CSR_GCFG_GCIP_SHIFT		16
#define  CSR_GCFG_GCIP			(UINT64_C(0xf) << CSR_GCFG_GCIP_SHIFT)
#define  CSR_GCFG_GCIP_ALL		(UINT64_C(0x1) << CSR_GCFG_GCIP_SHIFT)
#define  CSR_GCFG_GCIP_HIT		(UINT64_C(0x1) << (CSR_GCFG_GCIP_SHIFT + 1))
#define  CSR_GCFG_GCIP_SECURE		(UINT64_C(0x1) << (CSR_GCFG_GCIP_SHIFT + 2))
#define  CSR_GCFG_TORU_SHIFT		15
#define  CSR_GCFG_TORU			(UINT64_C(0x1) << CSR_GCFG_TORU_SHIFT)
#define  CSR_GCFG_TORUP_SHIFT		14
#define  CSR_GCFG_TORUP			(UINT64_C(0x1) << CSR_GCFG_TORUP_SHIFT)
#define  CSR_GCFG_TOP_SHIFT		13
#define  CSR_GCFG_TOP			(UINT64_C(0x1) << CSR_GCFG_TOP_SHIFT)
#define  CSR_GCFG_TOPP_SHIFT		12
#define  CSR_GCFG_TOPP			(UINT64_C(0x1) << CSR_GCFG_TOPP_SHIFT)
#define  CSR_GCFG_TOE_SHIFT		11
#define  CSR_GCFG_TOE			(UINT64_C(0x1) << CSR_GCFG_TOE_SHIFT)
#define  CSR_GCFG_TOEP_SHIFT		10
#define  CSR_GCFG_TOEP			(UINT64_C(0x1) << CSR_GCFG_TOEP_SHIFT)
#define  CSR_GCFG_TIT_SHIFT		9
#define  CSR_GCFG_TIT			(UINT64_C(0x1) << CSR_GCFG_TIT_SHIFT)
#define  CSR_GCFG_TITP_SHIFT		8
#define  CSR_GCFG_TITP			(UINT64_C(0x1) << CSR_GCFG_TITP_SHIFT)
#define  CSR_GCFG_SIT_SHIFT		7
#define  CSR_GCFG_SIT			(UINT64_C(0x1) << CSR_GCFG_SIT_SHIFT)
#define  CSR_GCFG_SITP_SHIFT		6
#define  CSR_GCFG_SITP			(UINT64_C(0x1) << CSR_GCFG_SITP_SHIFT)
#define  CSR_GCFG_MATC_SHITF		4
#define  CSR_GCFG_MATC_WIDTH		2
#define  CSR_GCFG_MATC_MASK		(UINT64_C(0x3) << CSR_GCFG_MATC_SHITF)
#define  CSR_GCFG_MATC_GUEST		(UINT64_C(0x0) << CSR_GCFG_MATC_SHITF)
#define  CSR_GCFG_MATC_ROOT		(UINT64_C(0x1) << CSR_GCFG_MATC_SHITF)
#define  CSR_GCFG_MATC_NEST		(UINT64_C(0x2) << CSR_GCFG_MATC_SHITF)

#define LOONGARCH_CSR_GINTC		0x52	/* Guest interrupt control */
#define  CSR_GINTC_HC_SHIFT		16
#define  CSR_GINTC_HC_WIDTH		8
#define  CSR_GINTC_HC			(UINT64_C(0xff) << CSR_GINTC_HC_SHIFT)
#define  CSR_GINTC_PIP_SHIFT		8
#define  CSR_GINTC_PIP_WIDTH		8
#define  CSR_GINTC_PIP			(UINT64_C(0xff) << CSR_GINTC_PIP_SHIFT)
#define  CSR_GINTC_VIP_SHIFT		0
#define  CSR_GINTC_VIP_WIDTH		8
#define  CSR_GINTC_VIP			(UINT64_C(0xff))

#define LOONGARCH_CSR_GCNTC		0x53	/* Guest timer offset */

/* LLBCTL register */
#define LOONGARCH_CSR_LLBCTL		0x60	/* LLBit control */
#define  CSR_LLBCTL_ROLLB_SHIFT		0
#define  CSR_LLBCTL_ROLLB		(UINT64_C(1) << CSR_LLBCTL_ROLLB_SHIFT)
#define  CSR_LLBCTL_WCLLB_SHIFT		1
#define  CSR_LLBCTL_WCLLB		(UINT64_C(1) << CSR_LLBCTL_WCLLB_SHIFT)
#define  CSR_LLBCTL_KLO_SHIFT		2
#define  CSR_LLBCTL_KLO			(UINT64_C(1) << CSR_LLBCTL_KLO_SHIFT)

/* Implement dependent */
#define LOONGARCH_CSR_IMPCTL1		0x80	/* Loongson config1 */
#define  CSR_MISPEC_SHIFT		20
#define  CSR_MISPEC_WIDTH		8
#define  CSR_MISPEC			(UINT64_C(0xff) << CSR_MISPEC_SHIFT)
#define  CSR_SSEN_SHIFT			18
#define  CSR_SSEN			(UINT64_C(1) << CSR_SSEN_SHIFT)
#define  CSR_SCRAND_SHIFT		17
#define  CSR_SCRAND			(UINT64_C(1) << CSR_SCRAND_SHIFT)
#define  CSR_LLEXCL_SHIFT		16
#define  CSR_LLEXCL			(UINT64_C(1) << CSR_LLEXCL_SHIFT)
#define  CSR_DISVC_SHIFT		15
#define  CSR_DISVC			(UINT64_C(1) << CSR_DISVC_SHIFT)
#define  CSR_VCLRU_SHIFT		14
#define  CSR_VCLRU			(UINT64_C(1) << CSR_VCLRU_SHIFT)
#define  CSR_DCLRU_SHIFT		13
#define  CSR_DCLRU			(UINT64_C(1) << CSR_DCLRU_SHIFT)
#define  CSR_FASTLDQ_SHIFT		12
#define  CSR_FASTLDQ			(UINT64_C(1) << CSR_FASTLDQ_SHIFT)
#define  CSR_USERCAC_SHIFT		11
#define  CSR_USERCAC			(UINT64_C(1) << CSR_USERCAC_SHIFT)
#define  CSR_ANTI_MISPEC_SHIFT		10
#define  CSR_ANTI_MISPEC		(UINT64_C(1) << CSR_ANTI_MISPEC_SHIFT)
#define  CSR_AUTO_FLUSHSFB_SHIFT	9
#define  CSR_AUTO_FLUSHSFB		(UINT64_C(1) << CSR_AUTO_FLUSHSFB_SHIFT)
#define  CSR_STFILL_SHIFT		8
#define  CSR_STFILL			(UINT64_C(1) << CSR_STFILL_SHIFT)
#define  CSR_LIFEP_SHIFT		7
#define  CSR_LIFEP			(UINT64_C(1) << CSR_LIFEP_SHIFT)
#define  CSR_LLSYNC_SHIFT		6
#define  CSR_LLSYNC			(UINT64_C(1) << CSR_LLSYNC_SHIFT)
#define  CSR_BRBTDIS_SHIFT		5
#define  CSR_BRBTDIS			(UINT64_C(1) << CSR_BRBTDIS_SHIFT)
#define  CSR_RASDIS_SHIFT		4
#define  CSR_RASDIS			(UINT64_C(1) << CSR_RASDIS_SHIFT)
#define  CSR_STPRE_SHIFT		2
#define  CSR_STPRE_WIDTH		2
#define  CSR_STPRE			(UINT64_C(3) << CSR_STPRE_SHIFT)
#define  CSR_INSTPRE_SHIFT		1
#define  CSR_INSTPRE			(UINT64_C(1) << CSR_INSTPRE_SHIFT)
#define  CSR_DATAPRE_SHIFT		0
#define  CSR_DATAPRE			(UINT64_C(1) << CSR_DATAPRE_SHIFT)

#define LOONGARCH_CSR_IMPCTL2		0x81	/* Loongson config2 */
#define  CSR_FLUSH_MTLB_SHIFT		0
#define  CSR_FLUSH_MTLB			(UINT64_C(1) << CSR_FLUSH_MTLB_SHIFT)
#define  CSR_FLUSH_STLB_SHIFT		1
#define  CSR_FLUSH_STLB			(UINT64_C(1) << CSR_FLUSH_STLB_SHIFT)
#define  CSR_FLUSH_DTLB_SHIFT		2
#define  CSR_FLUSH_DTLB			(UINT64_C(1) << CSR_FLUSH_DTLB_SHIFT)
#define  CSR_FLUSH_ITLB_SHIFT		3
#define  CSR_FLUSH_ITLB			(UINT64_C(1) << CSR_FLUSH_ITLB_SHIFT)
#define  CSR_FLUSH_BTAC_SHIFT		4
#define  CSR_FLUSH_BTAC			(UINT64_C(1) << CSR_FLUSH_BTAC_SHIFT)

#define LOONGARCH_CSR_GNMI		0x82

/* TLB Refill registers */
#define LOONGARCH_CSR_TLBRENTRY		0x88	/* TLB refill exception entry */
#define LOONGARCH_CSR_TLBRBADV		0x89	/* TLB refill badvaddr */
#define LOONGARCH_CSR_TLBRERA		0x8a	/* TLB refill ERA */
#define LOONGARCH_CSR_TLBRSAVE		0x8b	/* KScratch for TLB refill exception */
#define LOONGARCH_CSR_TLBRELO0		0x8c	/* TLB refill entrylo0 */
#define LOONGARCH_CSR_TLBRELO1		0x8d	/* TLB refill entrylo1 */
#define LOONGARCH_CSR_TLBREHI		0x8e	/* TLB refill entryhi */
#define  CSR_TLBREHI_PS_SHIFT		0
#define  CSR_TLBREHI_PS			(UINT64_C(0x3f) << CSR_TLBREHI_PS_SHIFT)
#define LOONGARCH_CSR_TLBRPRMD		0x8f	/* TLB refill mode info */

/* Machine Error registers */
#define LOONGARCH_CSR_MERRCTL		0x90	/* MERRCTL */
#define LOONGARCH_CSR_MERRINFO1		0x91	/* MError info1 */
#define LOONGARCH_CSR_MERRINFO2		0x92	/* MError info2 */
#define LOONGARCH_CSR_MERRENTRY		0x93	/* MError exception entry */
#define LOONGARCH_CSR_MERRERA		0x94	/* MError exception ERA */
#define LOONGARCH_CSR_MERRSAVE		0x95	/* KScratch for machine error exception */

#define LOONGARCH_CSR_CTAG		0x98	/* TagLo + TagHi */

#define LOONGARCH_CSR_PRID		0xc0

/* Shadow MCSR : 0xc0 ~ 0xff */
#define LOONGARCH_CSR_MCSR0		0xc0	/* CPUCFG0 and CPUCFG1 */
#define  MCSR0_INT_IMPL_SHIFT		58
#define  MCSR0_INT_IMPL			0
#define  MCSR0_IOCSR_BRD_SHIFT		57
#define  MCSR0_IOCSR_BRD		(UINT64_C(1) << MCSR0_IOCSR_BRD_SHIFT)
#define  MCSR0_HUGEPG_SHIFT		56
#define  MCSR0_HUGEPG			(UINT64_C(1) << MCSR0_HUGEPG_SHIFT)
#define  MCSR0_RPLMTLB_SHIFT		55
#define  MCSR0_RPLMTLB			(UINT64_C(1) << MCSR0_RPLMTLB_SHIFT)
#define  MCSR0_EP_SHIFT			54
#define  MCSR0_EP			(UINT64_C(1) << MCSR0_EP_SHIFT)
#define  MCSR0_RI_SHIFT			53
#define  MCSR0_RI			(UINT64_C(1) << MCSR0_RI_SHIFT)
#define  MCSR0_UAL_SHIFT		52
#define  MCSR0_UAL			(UINT64_C(1) << MCSR0_UAL_SHIFT)
#define  MCSR0_VABIT_SHIFT		44
#define  MCSR0_VABIT_WIDTH		8
#define  MCSR0_VABIT			(UINT64_C(0xff) << MCSR0_VABIT_SHIFT)
#define  VABIT_DEFAULT			0x2f
#define  MCSR0_PABIT_SHIFT		36
#define  MCSR0_PABIT_WIDTH		8
#define  MCSR0_PABIT			(UINT64_C(0xff) << MCSR0_PABIT_SHIFT)
#define  PABIT_DEFAULT			0x2f
#define  MCSR0_IOCSR_SHIFT		35
#define  MCSR0_IOCSR			(UINT64_C(1) << MCSR0_IOCSR_SHIFT)
#define  MCSR0_PAGING_SHIFT		34
#define  MCSR0_PAGING			(UINT64_C(1) << MCSR0_PAGING_SHIFT)
#define  MCSR0_GR64_SHIFT		33
#define  MCSR0_GR64			(UINT64_C(1) << MCSR0_GR64_SHIFT)
#define  GR64_DEFAULT			1
#define  MCSR0_GR32_SHIFT		32
#define  MCSR0_GR32			(UINT64_C(1) << MCSR0_GR32_SHIFT)
#define  GR32_DEFAULT			0
#define  MCSR0_PRID_WIDTH		32
#define  MCSR0_PRID			0x14C010

#define LOONGARCH_CSR_MCSR1		0xc1	/* CPUCFG2 and CPUCFG3 */
#define  MCSR1_HPFOLD_SHIFT		43
#define  MCSR1_HPFOLD			(UINT64_C(1) << MCSR1_HPFOLD_SHIFT)
#define  MCSR1_SPW_LVL_SHIFT		40
#define  MCSR1_SPW_LVL_WIDTH		3
#define  MCSR1_SPW_LVL			(UINT64_C(7) << MCSR1_SPW_LVL_SHIFT)
#define  MCSR1_ICACHET_SHIFT		39
#define  MCSR1_ICACHET			(UINT64_C(1) << MCSR1_ICACHET_SHIFT)
#define  MCSR1_ITLBT_SHIFT		38
#define  MCSR1_ITLBT			(UINT64_C(1) << MCSR1_ITLBT_SHIFT)
#define  MCSR1_LLDBAR_SHIFT		37
#define  MCSR1_LLDBAR			(UINT64_C(1) << MCSR1_LLDBAR_SHIFT)
#define  MCSR1_SCDLY_SHIFT		36
#define  MCSR1_SCDLY			(UINT64_C(1) << MCSR1_SCDLY_SHIFT)
#define  MCSR1_LLEXC_SHIFT		35
#define  MCSR1_LLEXC			(UINT64_C(1) << MCSR1_LLEXC_SHIFT)
#define  MCSR1_UCACC_SHIFT		34
#define  MCSR1_UCACC			(UINT64_C(1) << MCSR1_UCACC_SHIFT)
#define  MCSR1_SFB_SHIFT		33
#define  MCSR1_SFB			(UINT64_C(1) << MCSR1_SFB_SHIFT)
#define  MCSR1_CCDMA_SHIFT		32
#define  MCSR1_CCDMA			(UINT64_C(1) << MCSR1_CCDMA_SHIFT)
#define  MCSR1_LAMO_SHIFT		22
#define  MCSR1_LAMO			(UINT64_C(1) << MCSR1_LAMO_SHIFT)
#define  MCSR1_LSPW_SHIFT		21
#define  MCSR1_LSPW			(UINT64_C(1) << MCSR1_LSPW_SHIFT)
#define  MCSR1_MIPSBT_SHIFT		20
#define  MCSR1_MIPSBT			(UINT64_C(1) << MCSR1_MIPSBT_SHIFT)
#define  MCSR1_ARMBT_SHIFT		19
#define  MCSR1_ARMBT			(UINT64_C(1) << MCSR1_ARMBT_SHIFT)
#define  MCSR1_X86BT_SHIFT		18
#define  MCSR1_X86BT			(UINT64_C(1) << MCSR1_X86BT_SHIFT)
#define  MCSR1_LLFTPVERS_SHIFT		15
#define  MCSR1_LLFTPVERS_WIDTH		3
#define  MCSR1_LLFTPVERS		(UINT64_C(7) << MCSR1_LLFTPVERS_SHIFT)
#define  MCSR1_LLFTP_SHIFT		14
#define  MCSR1_LLFTP			(UINT64_C(1) << MCSR1_LLFTP_SHIFT)
#define  MCSR1_VZVERS_SHIFT		11
#define  MCSR1_VZVERS_WIDTH		3
#define  MCSR1_VZVERS			(UINT64_C(7) << MCSR1_VZVERS_SHIFT)
#define  MCSR1_VZ_SHIFT			10
#define  MCSR1_VZ			(UINT64_C(1) << MCSR1_VZ_SHIFT)
#define  MCSR1_CRYPTO_SHIFT		9
#define  MCSR1_CRYPTO			(UINT64_C(1) << MCSR1_CRYPTO_SHIFT)
#define  MCSR1_COMPLEX_SHIFT		8
#define  MCSR1_COMPLEX			(UINT64_C(1) << MCSR1_COMPLEX_SHIFT)
#define  MCSR1_LASX_SHIFT		7
#define  MCSR1_LASX			(UINT64_C(1) << MCSR1_LASX_SHIFT)
#define  MCSR1_LSX_SHIFT		6
#define  MCSR1_LSX			(UINT64_C(1) << MCSR1_LSX_SHIFT)
#define  MCSR1_FPVERS_SHIFT		3
#define  MCSR1_FPVERS_WIDTH		3
#define  MCSR1_FPVERS			(UINT64_C(7) << MCSR1_FPVERS_SHIFT)
#define  MCSR1_FPDP_SHIFT		2
#define  MCSR1_FPDP			(UINT64_C(1) << MCSR1_FPDP_SHIFT)
#define  MCSR1_FPSP_SHIFT		1
#define  MCSR1_FPSP			(UINT64_C(1) << MCSR1_FPSP_SHIFT)
#define  MCSR1_FP_SHIFT			0
#define  MCSR1_FP			(UINT64_C(1) << MCSR1_FP_SHIFT)

#define LOONGARCH_CSR_MCSR2		0xc2	/* CPUCFG4 and CPUCFG5 */
#define  MCSR2_CCDIV_SHIFT		48
#define  MCSR2_CCDIV_WIDTH		16
#define  MCSR2_CCDIV			(UINT64_C(0xffff) << MCSR2_CCDIV_SHIFT)
#define  MCSR2_CCMUL_SHIFT		32
#define  MCSR2_CCMUL_WIDTH		16
#define  MCSR2_CCMUL			(UINT64_C(0xffff) << MCSR2_CCMUL_SHIFT)
#define  MCSR2_CCFREQ_WIDTH		32
#define  MCSR2_CCFREQ			(UINT64_C(0xffffffff))
#define  CCFREQ_DEFAULT			0x5f5e100	/* 100MHz */

#define LOONGARCH_CSR_MCSR3		0xc3	/* CPUCFG6 */
#define  MCSR3_UPM_SHIFT		14
#define  MCSR3_UPM			(UINT64_C(1) << MCSR3_UPM_SHIFT)
#define  MCSR3_PMBITS_SHIFT		8
#define  MCSR3_PMBITS_WIDTH		6
#define  MCSR3_PMBITS			(UINT64_C(0x3f) << MCSR3_PMBITS_SHIFT)
#define  PMBITS_DEFAULT			0x40
#define  MCSR3_PMNUM_SHIFT		4
#define  MCSR3_PMNUM_WIDTH		4
#define  MCSR3_PMNUM			(UINT64_C(0xf) << MCSR3_PMNUM_SHIFT)
#define  MCSR3_PAMVER_SHIFT		1
#define  MCSR3_PAMVER_WIDTH		3
#define  MCSR3_PAMVER			(UINT64_C(0x7) << MCSR3_PAMVER_SHIFT)
#define  MCSR3_PMP_SHIFT		0
#define  MCSR3_PMP			(UINT64_C(1) << MCSR3_PMP_SHIFT)

#define LOONGARCH_CSR_MCSR8		0xc8	/* CPUCFG16 and CPUCFG17 */
#define  MCSR8_L1I_SIZE_SHIFT		56
#define  MCSR8_L1I_SIZE_WIDTH		7
#define  MCSR8_L1I_SIZE			(UINT64_C(0x7f) << MCSR8_L1I_SIZE_SHIFT)
#define  MCSR8_L1I_IDX_SHIFT		48
#define  MCSR8_L1I_IDX_WIDTH		8
#define  MCSR8_L1I_IDX			(UINT64_C(0xff) << MCSR8_L1I_IDX_SHIFT)
#define  MCSR8_L1I_WAY_SHIFT		32
#define  MCSR8_L1I_WAY_WIDTH		16
#define  MCSR8_L1I_WAY			(UINT64_C(0xffff) << MCSR8_L1I_WAY_SHIFT)
#define  MCSR8_L3DINCL_SHIFT		16
#define  MCSR8_L3DINCL			(UINT64_C(1) << MCSR8_L3DINCL_SHIFT)
#define  MCSR8_L3DPRIV_SHIFT		15
#define  MCSR8_L3DPRIV			(UINT64_C(1) << MCSR8_L3DPRIV_SHIFT)
#define  MCSR8_L3DPRE_SHIFT		14
#define  MCSR8_L3DPRE			(UINT64_C(1) << MCSR8_L3DPRE_SHIFT)
#define  MCSR8_L3IUINCL_SHIFT		13
#define  MCSR8_L3IUINCL			(UINT64_C(1) << MCSR8_L3IUINCL_SHIFT)
#define  MCSR8_L3IUPRIV_SHIFT		12
#define  MCSR8_L3IUPRIV			(UINT64_C(1) << MCSR8_L3IUPRIV_SHIFT)
#define  MCSR8_L3IUUNIFY_SHIFT		11
#define  MCSR8_L3IUUNIFY		(UINT64_C(1) << MCSR8_L3IUUNIFY_SHIFT)
#define  MCSR8_L3IUPRE_SHIFT		10
#define  MCSR8_L3IUPRE			(UINT64_C(1) << MCSR8_L3IUPRE_SHIFT)
#define  MCSR8_L2DINCL_SHIFT		9
#define  MCSR8_L2DINCL			(UINT64_C(1) << MCSR8_L2DINCL_SHIFT)
#define  MCSR8_L2DPRIV_SHIFT		8
#define  MCSR8_L2DPRIV			(UINT64_C(1) << MCSR8_L2DPRIV_SHIFT)
#define  MCSR8_L2DPRE_SHIFT		7
#define  MCSR8_L2DPRE			(UINT64_C(1) << MCSR8_L2DPRE_SHIFT)
#define  MCSR8_L2IUINCL_SHIFT		6
#define  MCSR8_L2IUINCL			(UINT64_C(1) << MCSR8_L2IUINCL_SHIFT)
#define  MCSR8_L2IUPRIV_SHIFT		5
#define  MCSR8_L2IUPRIV			(UINT64_C(1) << MCSR8_L2IUPRIV_SHIFT)
#define  MCSR8_L2IUUNIFY_SHIFT		4
#define  MCSR8_L2IUUNIFY		(UINT64_C(1) << MCSR8_L2IUUNIFY_SHIFT)
#define  MCSR8_L2IUPRE_SHIFT		3
#define  MCSR8_L2IUPRE			(UINT64_C(1) << MCSR8_L2IUPRE_SHIFT)
#define  MCSR8_L1DPRE_SHIFT		2
#define  MCSR8_L1DPRE			(UINT64_C(1) << MCSR8_L1DPRE_SHIFT)
#define  MCSR8_L1IUUNIFY_SHIFT		1
#define  MCSR8_L1IUUNIFY		(UINT64_C(1) << MCSR8_L1IUUNIFY_SHIFT)
#define  MCSR8_L1IUPRE_SHIFT		0
#define  MCSR8_L1IUPRE			(UINT64_C(1) << MCSR8_L1IUPRE_SHIFT)

#define LOONGARCH_CSR_MCSR9		0xc9	/* CPUCFG18 and CPUCFG19 */
#define  MCSR9_L2U_SIZE_SHIFT		56
#define  MCSR9_L2U_SIZE_WIDTH		7
#define  MCSR9_L2U_SIZE			(UINT64_C(0x7f) << MCSR9_L2U_SIZE_SHIFT)
#define  MCSR9_L2U_IDX_SHIFT		48
#define  MCSR9_L2U_IDX_WIDTH		8
#define  MCSR9_L2U_IDX			(UINT64_C(0xff) << MCSR9_IDX_LOG_SHIFT)
#define  MCSR9_L2U_WAY_SHIFT		32
#define  MCSR9_L2U_WAY_WIDTH		16
#define  MCSR9_L2U_WAY			(UINT64_C(0xffff) << MCSR9_L2U_WAY_SHIFT)
#define  MCSR9_L1D_SIZE_SHIFT		24
#define  MCSR9_L1D_SIZE_WIDTH		7
#define  MCSR9_L1D_SIZE			(UINT64_C(0x7f) << MCSR9_L1D_SIZE_SHIFT)
#define  MCSR9_L1D_IDX_SHIFT		16
#define  MCSR9_L1D_IDX_WIDTH		8
#define  MCSR9_L1D_IDX			(UINT64_C(0xff) << MCSR9_L1D_IDX_SHIFT)
#define  MCSR9_L1D_WAY_SHIFT		0
#define  MCSR9_L1D_WAY_WIDTH		16
#define  MCSR9_L1D_WAY			(UINT64_C(0xffff) << MCSR9_L1D_WAY_SHIFT)

#define LOONGARCH_CSR_MCSR10		0xca	/* CPUCFG20 */
#define  MCSR10_L3U_SIZE_SHIFT		24
#define  MCSR10_L3U_SIZE_WIDTH		7
#define  MCSR10_L3U_SIZE		(UINT64_C(0x7f) << MCSR10_L3U_SIZE_SHIFT)
#define  MCSR10_L3U_IDX_SHIFT		16
#define  MCSR10_L3U_IDX_WIDTH		8
#define  MCSR10_L3U_IDX			(UINT64_C(0xff) << MCSR10_L3U_IDX_SHIFT)
#define  MCSR10_L3U_WAY_SHIFT		0
#define  MCSR10_L3U_WAY_WIDTH		16
#define  MCSR10_L3U_WAY			(UINT64_C(0xffff) << MCSR10_L3U_WAY_SHIFT)

#define LOONGARCH_CSR_MCSR24		0xf0	/* cpucfg48 */
#define  MCSR24_RAMCG_SHIFT		3
#define  MCSR24_RAMCG			(UINT64_C(1) << MCSR24_RAMCG_SHIFT)
#define  MCSR24_VFPUCG_SHIFT		2
#define  MCSR24_VFPUCG			(UINT64_C(1) << MCSR24_VFPUCG_SHIFT)
#define  MCSR24_NAPEN_SHIFT		1
#define  MCSR24_NAPEN			(UINT64_C(1) << MCSR24_NAPEN_SHIFT)
#define  MCSR24_MCSRLOCK_SHIFT		0
#define  MCSR24_MCSRLOCK		(UINT64_C(1) << MCSR24_MCSRLOCK_SHIFT)

/* Uncached accelerate windows registers */
#define LOONGARCH_CSR_UCAWIN		0x100
#define LOONGARCH_CSR_UCAWIN0_LO	0x102
#define LOONGARCH_CSR_UCAWIN0_HI	0x103
#define LOONGARCH_CSR_UCAWIN1_LO	0x104
#define LOONGARCH_CSR_UCAWIN1_HI	0x105
#define LOONGARCH_CSR_UCAWIN2_LO	0x106
#define LOONGARCH_CSR_UCAWIN2_HI	0x107
#define LOONGARCH_CSR_UCAWIN3_LO	0x108
#define LOONGARCH_CSR_UCAWIN3_HI	0x109

/* Direct Map windows registers */
#define LOONGARCH_CSR_DMWIN0		0x180	/* 64 direct map win0: MEM & IF */
#define LOONGARCH_CSR_DMWIN1		0x181	/* 64 direct map win1: MEM & IF */
#define LOONGARCH_CSR_DMWIN2		0x182	/* 64 direct map win2: MEM */
#define LOONGARCH_CSR_DMWIN3		0x183	/* 64 direct map win3: MEM */

/* Direct Map window 0/1 */
#define CSR_DMW0_PLV0		_CONST64_(1 << 0)
#define CSR_DMW0_VSEG		_CONST64_(0x8000)
#define CSR_DMW0_BASE		(CSR_DMW0_VSEG << DMW_PABITS)
#define CSR_DMW0_INIT		(CSR_DMW0_BASE | CSR_DMW0_PLV0)

#define CSR_DMW1_PLV0		_CONST64_(1 << 0)
#define CSR_DMW1_MAT		_CONST64_(1 << 4)
#define CSR_DMW1_VSEG		_CONST64_(0x9000)
#define CSR_DMW1_BASE		(CSR_DMW1_VSEG << DMW_PABITS)
#define CSR_DMW1_INIT		(CSR_DMW1_BASE | CSR_DMW1_MAT | CSR_DMW1_PLV0)

/* Performance Counter registers */
#define LOONGARCH_CSR_PERFCTRL0		0x200	/* 32 perf event 0 config */
#define LOONGARCH_CSR_PERFCNTR0		0x201	/* 64 perf event 0 count value */
#define LOONGARCH_CSR_PERFCTRL1		0x202	/* 32 perf event 1 config */
#define LOONGARCH_CSR_PERFCNTR1		0x203	/* 64 perf event 1 count value */
#define LOONGARCH_CSR_PERFCTRL2		0x204	/* 32 perf event 2 config */
#define LOONGARCH_CSR_PERFCNTR2		0x205	/* 64 perf event 2 count value */
#define LOONGARCH_CSR_PERFCTRL3		0x206	/* 32 perf event 3 config */
#define LOONGARCH_CSR_PERFCNTR3		0x207	/* 64 perf event 3 count value */
#define  CSR_PERFCTRL_PLV0		(UINT64_C(1) << 16)
#define  CSR_PERFCTRL_PLV1		(UINT64_C(1) << 17)
#define  CSR_PERFCTRL_PLV2		(UINT64_C(1) << 18)
#define  CSR_PERFCTRL_PLV3		(UINT64_C(1) << 19)
#define  CSR_PERFCTRL_IE		(UINT64_C(1) << 20)
#define  CSR_PERFCTRL_EVENT		0x3ff

/* Debug registers */
#define LOONGARCH_CSR_MWPC		0x300	/* data breakpoint config */
#define LOONGARCH_CSR_MWPS		0x301	/* data breakpoint status */

#define LOONGARCH_CSR_DB0ADDR		0x310	/* data breakpoint 0 address */
#define LOONGARCH_CSR_DB0MASK		0x311	/* data breakpoint 0 mask */
#define LOONGARCH_CSR_DB0CTL		0x312	/* data breakpoint 0 control */
#define LOONGARCH_CSR_DB0ASID		0x313	/* data breakpoint 0 asid */

#define LOONGARCH_CSR_DB1ADDR		0x318	/* data breakpoint 1 address */
#define LOONGARCH_CSR_DB1MASK		0x319	/* data breakpoint 1 mask */
#define LOONGARCH_CSR_DB1CTL		0x31a	/* data breakpoint 1 control */
#define LOONGARCH_CSR_DB1ASID		0x31b	/* data breakpoint 1 asid */

#define LOONGARCH_CSR_DB2ADDR		0x320	/* data breakpoint 2 address */
#define LOONGARCH_CSR_DB2MASK		0x321	/* data breakpoint 2 mask */
#define LOONGARCH_CSR_DB2CTL		0x322	/* data breakpoint 2 control */
#define LOONGARCH_CSR_DB2ASID		0x323	/* data breakpoint 2 asid */

#define LOONGARCH_CSR_DB3ADDR		0x328	/* data breakpoint 3 address */
#define LOONGARCH_CSR_DB3MASK		0x329	/* data breakpoint 3 mask */
#define LOONGARCH_CSR_DB3CTL		0x32a	/* data breakpoint 3 control */
#define LOONGARCH_CSR_DB3ASID		0x32b	/* data breakpoint 3 asid */

#define LOONGARCH_CSR_DB4ADDR		0x330	/* data breakpoint 4 address */
#define LOONGARCH_CSR_DB4MASK		0x331	/* data breakpoint 4 maks */
#define LOONGARCH_CSR_DB4CTL		0x332	/* data breakpoint 4 control */
#define LOONGARCH_CSR_DB4ASID		0x333	/* data breakpoint 4 asid */

#define LOONGARCH_CSR_DB5ADDR		0x338	/* data breakpoint 5 address */
#define LOONGARCH_CSR_DB5MASK		0x339	/* data breakpoint 5 mask */
#define LOONGARCH_CSR_DB5CTL		0x33a	/* data breakpoint 5 control */
#define LOONGARCH_CSR_DB5ASID		0x33b	/* data breakpoint 5 asid */

#define LOONGARCH_CSR_DB6ADDR		0x340	/* data breakpoint 6 address */
#define LOONGARCH_CSR_DB6MASK		0x341	/* data breakpoint 6 mask */
#define LOONGARCH_CSR_DB6CTL		0x342	/* data breakpoint 6 control */
#define LOONGARCH_CSR_DB6ASID		0x343	/* data breakpoint 6 asid */

#define LOONGARCH_CSR_DB7ADDR		0x348	/* data breakpoint 7 address */
#define LOONGARCH_CSR_DB7MASK		0x349	/* data breakpoint 7 mask */
#define LOONGARCH_CSR_DB7CTL		0x34a	/* data breakpoint 7 control */
#define LOONGARCH_CSR_DB7ASID		0x34b	/* data breakpoint 7 asid */

#define LOONGARCH_CSR_FWPC		0x380	/* instruction breakpoint config */
#define LOONGARCH_CSR_FWPS		0x381	/* instruction breakpoint status */

#define LOONGARCH_CSR_IB0ADDR		0x390	/* inst breakpoint 0 address */
#define LOONGARCH_CSR_IB0MASK		0x391	/* inst breakpoint 0 mask */
#define LOONGARCH_CSR_IB0CTL		0x392	/* inst breakpoint 0 control */
#define LOONGARCH_CSR_IB0ASID		0x393	/* inst breakpoint 0 asid */

#define LOONGARCH_CSR_IB1ADDR		0x398	/* inst breakpoint 1 address */
#define LOONGARCH_CSR_IB1MASK		0x399	/* inst breakpoint 1 mask */
#define LOONGARCH_CSR_IB1CTL		0x39a	/* inst breakpoint 1 control */
#define LOONGARCH_CSR_IB1ASID		0x39b	/* inst breakpoint 1 asid */

#define LOONGARCH_CSR_IB2ADDR		0x3a0	/* inst breakpoint 2 address */
#define LOONGARCH_CSR_IB2MASK		0x3a1	/* inst breakpoint 2 mask */
#define LOONGARCH_CSR_IB2CTL		0x3a2	/* inst breakpoint 2 control */
#define LOONGARCH_CSR_IB2ASID		0x3a3	/* inst breakpoint 2 asid */

#define LOONGARCH_CSR_IB3ADDR		0x3a8	/* inst breakpoint 3 address */
#define LOONGARCH_CSR_IB3MASK		0x3a9	/* breakpoint 3 mask */
#define LOONGARCH_CSR_IB3CTL		0x3aa	/* inst breakpoint 3 control */
#define LOONGARCH_CSR_IB3ASID		0x3ab	/* inst breakpoint 3 asid */

#define LOONGARCH_CSR_IB4ADDR		0x3b0	/* inst breakpoint 4 address */
#define LOONGARCH_CSR_IB4MASK		0x3b1	/* inst breakpoint 4 mask */
#define LOONGARCH_CSR_IB4CTL		0x3b2	/* inst breakpoint 4 control */
#define LOONGARCH_CSR_IB4ASID		0x3b3	/* inst breakpoint 4 asid */

#define LOONGARCH_CSR_IB5ADDR		0x3b8	/* inst breakpoint 5 address */
#define LOONGARCH_CSR_IB5MASK		0x3b9	/* inst breakpoint 5 mask */
#define LOONGARCH_CSR_IB5CTL		0x3ba	/* inst breakpoint 5 control */
#define LOONGARCH_CSR_IB5ASID		0x3bb	/* inst breakpoint 5 asid */

#define LOONGARCH_CSR_IB6ADDR		0x3c0	/* inst breakpoint 6 address */
#define LOONGARCH_CSR_IB6MASK		0x3c1	/* inst breakpoint 6 mask */
#define LOONGARCH_CSR_IB6CTL		0x3c2	/* inst breakpoint 6 control */
#define LOONGARCH_CSR_IB6ASID		0x3c3	/* inst breakpoint 6 asid */

#define LOONGARCH_CSR_IB7ADDR		0x3c8	/* inst breakpoint 7 address */
#define LOONGARCH_CSR_IB7MASK		0x3c9	/* inst breakpoint 7 mask */
#define LOONGARCH_CSR_IB7CTL		0x3ca	/* inst breakpoint 7 control */
#define LOONGARCH_CSR_IB7ASID		0x3cb	/* inst breakpoint 7 asid */

#define LOONGARCH_CSR_DEBUG		0x500	/* debug config */
#define LOONGARCH_CSR_DERA		0x501	/* debug era */
#define LOONGARCH_CSR_DESAVE		0x502	/* debug save */

/*
 * CSR_ECFG IM
 */
#define ECFG0_IM		0x00001fff
#define ECFGB_SIP0		0
#define ECFGF_SIP0		(UINT64_C(1) << ECFGB_SIP0)
#define ECFGB_SIP1		1
#define ECFGF_SIP1		(UINT64_C(1) << ECFGB_SIP1)
#define ECFGB_IP0		2
#define ECFGF_IP0		(UINT64_C(1) << ECFGB_IP0)
#define ECFGB_IP1		3
#define ECFGF_IP1		(UINT64_C(1) << ECFGB_IP1)
#define ECFGB_IP2		4
#define ECFGF_IP2		(UINT64_C(1) << ECFGB_IP2)
#define ECFGB_IP3		5
#define ECFGF_IP3		(UINT64_C(1) << ECFGB_IP3)
#define ECFGB_IP4		6
#define ECFGF_IP4		(UINT64_C(1) << ECFGB_IP4)
#define ECFGB_IP5		7
#define ECFGF_IP5		(UINT64_C(1) << ECFGB_IP5)
#define ECFGB_IP6		8
#define ECFGF_IP6		(UINT64_C(1) << ECFGB_IP6)
#define ECFGB_IP7		9
#define ECFGF_IP7		(UINT64_C(1) << ECFGB_IP7)
#define ECFGB_PMC		10
#define ECFGF_PMC		(UINT64_C(1) << ECFGB_PMC)
#define ECFGB_TIMER		11
#define ECFGF_TIMER		(UINT64_C(1) << ECFGB_TIMER)
#define ECFGB_IPI		12
#define ECFGF_IPI		(UINT64_C(1) << ECFGB_IPI)
#define ECFGF(hwirq)		(UINT64_C(1) << hwirq)

#define ESTATF_IP		0x00001fff

#define LOONGARCH_IOCSR_FEATURES	0x8
#define  IOCSRF_TEMP			BIT_ULL(0)
#define  IOCSRF_NODECNT			BIT_ULL(1)
#define  IOCSRF_MSI			BIT_ULL(2)
#define  IOCSRF_EXTIOI			BIT_ULL(3)
#define  IOCSRF_CSRIPI			BIT_ULL(4)
#define  IOCSRF_FREQCSR			BIT_ULL(5)
#define  IOCSRF_FREQSCALE		BIT_ULL(6)
#define  IOCSRF_DVFSV1			BIT_ULL(7)
#define  IOCSRF_EIODECODE		BIT_ULL(9)
#define  IOCSRF_FLATMODE		BIT_ULL(10)
#define  IOCSRF_VM			BIT_ULL(11)

#define LOONGARCH_IOCSR_VENDOR		0x10

#define LOONGARCH_IOCSR_CPUNAME		0x20

#define LOONGARCH_IOCSR_NODECNT		0x408

#define LOONGARCH_IOCSR_MISC_FUNC	0x420
#define  IOCSR_MISC_FUNC_TIMER_RESET	BIT_ULL(21)
#define  IOCSR_MISC_FUNC_EXT_IOI_EN	BIT_ULL(48)

#define LOONGARCH_IOCSR_CPUTEMP		0x428


// /* User Trap Registers */

// #define CSR_USTATUS         0x000
// #define CSR_UIE             0x004
// #define CSR_UTVEC           0x005

// /* User Trap Handling Registers */

// #define CSR_USCRATCH        0x040
// #define CSR_UEPC            0x041
// #define CSR_UCAUSE          0x042
// #define CSR_UTVAL           0x043
// #define CSR_UIP             0x044

// /* User Floating-Point Registers */

// #define CSR_FFLAGS          0x001
// #define CSR_FRM             0x002
// #define CSR_FCSR            0x003

// /* User Counter/Times Registers */

// #define CSR_CYCLE           0xc00
// #define CSR_TIME            0xc01
// #define CSR_INSTRET         0xc02
// #define CSR_HPCOUNTER3      0xc03
// #define CSR_HPCOUNTER4      0xc04
// #define CSR_HPCOUNTER5      0xc05
// #define CSR_HPCOUNTER6      0xc06
// #define CSR_HPCOUNTER7      0xc07
// #define CSR_HPCOUNTER8      0xc08
// #define CSR_HPCOUNTER9      0xc09
// #define CSR_HPCOUNTER10     0xc0a
// #define CSR_HPCOUNTER11     0xc0b
// #define CSR_HPCOUNTER12     0xc0c
// #define CSR_HPCOUNTER13     0xc0d
// #define CSR_HPCOUNTER14     0xc0e
// #define CSR_HPCOUNTER15     0xc0f
// #define CSR_HPCOUNTER16     0xc10
// #define CSR_HPCOUNTER17     0xc11
// #define CSR_HPCOUNTER18     0xc12
// #define CSR_HPCOUNTER19     0xc13
// #define CSR_HPCOUNTER20     0xc14
// #define CSR_HPCOUNTER21     0xc15
// #define CSR_HPCOUNTER22     0xc16
// #define CSR_HPCOUNTER24     0xc17
// #define CSR_HPCOUNTER25     0xc18
// #define CSR_HPCOUNTER26     0xc19
// #define CSR_HPCOUNTER27     0xc1a
// #define CSR_HPCOUNTER28     0xc1b
// #define CSR_HPCOUNTER29     0xc1c
// #define CSR_HPCOUNTER30     0xc1d
// #define CSR_HPCOUNTER31     0xc1f
// #define CSR_CYCLEH          0xc80
// #define CSR_TIMEH           0xc81
// #define CSR_INSTRETH        0xc82
// #define CSR_HPCOUNTER3H     0xc83
// #define CSR_HPCOUNTER4H     0xc84
// #define CSR_HPCOUNTER5H     0xc85
// #define CSR_HPCOUNTER6H     0xc86
// #define CSR_HPCOUNTER7H     0xc87
// #define CSR_HPCOUNTER8H     0xc88
// #define CSR_HPCOUNTER9H     0xc89
// #define CSR_HPCOUNTER10H    0xc8a
// #define CSR_HPCOUNTER11H    0xc8b
// #define CSR_HPCOUNTER12H    0xc8c
// #define CSR_HPCOUNTER13H    0xc8d
// #define CSR_HPCOUNTER14H    0xc8e
// #define CSR_HPCOUNTER15H    0xc8f
// #define CSR_HPCOUNTER16H    0xc90
// #define CSR_HPCOUNTER17H    0xc91
// #define CSR_HPCOUNTER18H    0xc92
// #define CSR_HPCOUNTER19H    0xc93
// #define CSR_HPCOUNTER20H    0xc94
// #define CSR_HPCOUNTER21H    0xc95
// #define CSR_HPCOUNTER22H    0xc96
// #define CSR_HPCOUNTER24H    0xc97
// #define CSR_HPCOUNTER25H    0xc98
// #define CSR_HPCOUNTER26H    0xc99
// #define CSR_HPCOUNTER27H    0xc9a
// #define CSR_HPCOUNTER28H    0xc9b
// #define CSR_HPCOUNTER29H    0xc9c
// #define CSR_HPCOUNTER30H    0xc9d
// #define CSR_HPCOUNTER31H    0xc9f

// /* Supervisor Trap Setup Registers */

// #define CSR_SSTATUS         0x100
// #define CSR_SEDELEG         0x102
// #define CSR_SIDELEG         0x103
// #define CSR_SIE             0x104
// #define CSR_STVEC           0x105
// #define CSR_SCOUNTEREN      0x106

// /* Supervisor Trap Handling Registers */

// #define CSR_SSCRATCH        0x140
// #define CSR_SEPC            0x141
// #define CSR_SCAUSE          0x142
// #define CSR_STVAL           0x143
// #define CSR_SIP             0x144

// /* Supervisor Protection and Translation Registers */

// #define CSR_SATP            0x180

// /* Machine Information Registers */

// #define CSR_MVENDORID       0xf11
// #define CSR_MARCHID         0xf12
// #define CSR_MIMPID          0xf13
// #define CSR_MHARTID         0xf14

// /* Machine Trap Registers */

// #define CSR_MSTATUS         0x300
// #define CSR_MISA            0x301
// #define CSR_MEDELEG         0x302
// #define CSR_MIDELEG         0x303
// #define CSR_MIE             0x304
// #define CSR_MTVEC           0x305
// #define CSR_MCOUNTEREN      0x306

// /* Machine Trap Handling */

// #define CSR_MSCRATCH        0x340
// #define CSR_MEPC            0x341
// #define CSR_MCAUSE          0x342
// #define CSR_MTVAL           0x343
// #define CSR_MIP             0x344

// /* Machine Protection and Translation */

// #define CSR_PMPCFG0         0x3a0
// #define CSR_PMPCFG1         0x3a1
// #define CSR_PMPCFG2         0x3a2
// #define CSR_PMPCFG3         0x3a3
// #define CSR_PMPADDR0        0x3b0
// #define CSR_PMPADDR1        0x3b1
// #define CSR_PMPADDR2        0x3b2
// #define CSR_PMPADDR3        0x3b3
// #define CSR_PMPADDR4        0x3b4
// #define CSR_PMPADDR5        0x3b5
// #define CSR_PMPADDR6        0x3b6
// #define CSR_PMPADDR7        0x3b7
// #define CSR_PMPADDR8        0x3b8
// #define CSR_PMPADDR9        0x3b9
// #define CSR_PMPADDR10       0x3ba
// #define CSR_PMPADDR11       0x3bb
// #define CSR_PMPADDR12       0x3bc
// #define CSR_PMPADDR13       0x3bd
// #define CSR_PMPADDR14       0x3be
// #define CSR_PMPADDR15       0x3bf

// /* Machine Timers and Counters */

// #define CSR_MCYCLE          0xb00
// #define CSR_MINSTRET        0xb02
// #define CSR_MHPMCOUNTER3    0xb03
// #define CSR_MHPMCOUNTER4    0xb04
// #define CSR_MHPMCOUNTER5    0xb05
// #define CSR_MHPMCOUNTER6    0xb06
// #define CSR_MHPMCOUNTER7    0xb07
// #define CSR_MHPMCOUNTER8    0xb08
// #define CSR_MHPMCOUNTER9    0xb09
// #define CSR_MHPMCOUNTER10   0xb0a
// #define CSR_MHPMCOUNTER11   0xb0b
// #define CSR_MHPMCOUNTER12   0xb0c
// #define CSR_MHPMCOUNTER13   0xb0d
// #define CSR_MHPMCOUNTER14   0xb0e
// #define CSR_MHPMCOUNTER15   0xb0f
// #define CSR_MHPMCOUNTER16   0xb10
// #define CSR_MHPMCOUNTER17   0xb11
// #define CSR_MHPMCOUNTER18   0xb12
// #define CSR_MHPMCOUNTER19   0xb13
// #define CSR_MHPMCOUNTER20   0xb14
// #define CSR_MHPMCOUNTER21   0xb15
// #define CSR_MHPMCOUNTER22   0xb16
// #define CSR_MHPMCOUNTER23   0xb17
// #define CSR_MHPMCOUNTER24   0xb18
// #define CSR_MHPMCOUNTER25   0xb19
// #define CSR_MHPMCOUNTER26   0xb1a
// #define CSR_MHPMCOUNTER27   0xb1b
// #define CSR_MHPMCOUNTER28   0xb1c
// #define CSR_MHPMCOUNTER29   0xb1d
// #define CSR_MHPMCOUNTER30   0xb1e
// #define CSR_MHPMCOUNTER31   0xb1f
// #define CSR_MCYCLEH         0xb80
// #define CSR_MINSTRETH       0xb82
// #define CSR_MHPMCOUNTER3H   0xb83
// #define CSR_MHPMCOUNTER4H   0xb84
// #define CSR_MHPMCOUNTER5H   0xb85
// #define CSR_MHPMCOUNTER6H   0xb86
// #define CSR_MHPMCOUNTER7H   0xb87
// #define CSR_MHPMCOUNTER8H   0xb88
// #define CSR_MHPMCOUNTER9H   0xb89
// #define CSR_MHPMCOUNTER10H  0xb8a
// #define CSR_MHPMCOUNTER11H  0xb8b
// #define CSR_MHPMCOUNTER12H  0xb8c
// #define CSR_MHPMCOUNTER13H  0xb8d
// #define CSR_MHPMCOUNTER14H  0xb8e
// #define CSR_MHPMCOUNTER15H  0xb8f
// #define CSR_MHPMCOUNTER16H  0xb90
// #define CSR_MHPMCOUNTER17H  0xb91
// #define CSR_MHPMCOUNTER18H  0xb92
// #define CSR_MHPMCOUNTER19H  0xb93
// #define CSR_MHPMCOUNTER20H  0xb94
// #define CSR_MHPMCOUNTER21H  0xb95
// #define CSR_MHPMCOUNTER22H  0xb96
// #define CSR_MHPMCOUNTER23H  0xb97
// #define CSR_MHPMCOUNTER24H  0xb98
// #define CSR_MHPMCOUNTER25H  0xb99
// #define CSR_MHPMCOUNTER26H  0xb9a
// #define CSR_MHPMCOUNTER27H  0xb9b
// #define CSR_MHPMCOUNTER28H  0xb9c
// #define CSR_MHPMCOUNTER29H  0xb9d
// #define CSR_MHPMCOUNTER30H  0xb9e
// #define CSR_MHPMCOUNTER31H  0xb9f

// /* Machine Counter Setup */

// #define CSR_MPHEVENT3       0x323
// #define CSR_MPHEVENT4       0x324
// #define CSR_MPHEVENT5       0x325
// #define CSR_MPHEVENT6       0x326
// #define CSR_MPHEVENT7       0x327
// #define CSR_MPHEVENT8       0x328
// #define CSR_MPHEVENT9       0x329
// #define CSR_MPHEVENT10      0x32a
// #define CSR_MPHEVENT11      0x32b
// #define CSR_MPHEVENT12      0x32c
// #define CSR_MPHEVENT13      0x32d
// #define CSR_MPHEVENT14      0x32e
// #define CSR_MPHEVENT15      0x32f
// #define CSR_MPHEVENT16      0x330
// #define CSR_MPHEVENT17      0x331
// #define CSR_MPHEVENT18      0x332
// #define CSR_MPHEVENT19      0x333
// #define CSR_MPHEVENT20      0x334
// #define CSR_MPHEVENT21      0x335
// #define CSR_MPHEVENT22      0x336
// #define CSR_MPHEVENT23      0x337
// #define CSR_MPHEVENT24      0x338
// #define CSR_MPHEVENT25      0x339
// #define CSR_MPHEVENT26      0x33a
// #define CSR_MPHEVENT27      0x33b
// #define CSR_MPHEVENT28      0x33c
// #define CSR_MPHEVENT29      0x33d
// #define CSR_MPHEVENT30      0x33e
// #define CSR_MPHEVENT31      0x33f

// /* Debug/Trace Registers */

// #define CSR_TSELECT         0x7a0
// #define CSR_TDATA1          0x7a1
// #define CSR_TDATA2          0x7a2
// #define CSR_TDATA3          0x7a3

// /* Debug interface CSRs */

// #define CSR_DCSR            0x7b0
// #define CSR_DPC             0x7b1
// #define CSR_DSCRATCH        0x7b2

// /* In mstatus register */

// #define MSTATUS_UIE         (0x1 << 0)  /* User Interrupt Enable */
// #define MSTATUS_SIE         (0x1 << 1)  /* Supervisor Interrupt Enable */
// #define MSTATUS_MIE         (0x1 << 3)  /* Machine Interrupt Enable */
// #define MSTATUS_SPIE        (0x1 << 5)  /* Supervisor Previous Interrupt Enable */
// #define MSTATUS_MPIE        (0x1 << 7)  /* Machine Previous Interrupt Enable */
// #define MSTATUS_SPPU        (0x0 << 8)  /* Supervisor Previous Privilege (u-mode) */
// #define MSTATUS_SPPS        (0x1 << 8)  /* Supervisor Previous Privilege (s-mode) */
// #define MSTATUS_MPPU        (0x0 << 11) /* Machine Previous Privilege (u-mode) */
// #define MSTATUS_MPPS        (0x1 << 11) /* Machine Previous Privilege (s-mode) */
// #define MSTATUS_MPPM        (0x3 << 11) /* Machine Previous Privilege (m-mode) */
// #define MSTATUS_MPP_MASK    (0x3 << 11)
// #define MSTATUS_FS          (0x3 << 13) /* Machine Floating-point Status */
// #define MSTATUS_FS_INIT     (0x1 << 13)
// #define MSTATUS_FS_CLEAN    (0x2 << 13)
// #define MSTATUS_FS_DIRTY    (0x3 << 13)
// #define MSTATUS_MPRV        (0x1 << 17) /* Modify Privilege */
// #define MSTATUS_SUM         (0x1 << 18) /* S mode access to U mode memory */
// #define MSTATUS_MXR         (0x1 << 19) /* Make executable / readable */
// #define MSTATUS_TVM         (0x1 << 20) /* Trap access to satp from S mode */
// #define MSTATUS_TW          (0x1 << 21) /* Trap WFI instruction from S mode */
// #define MSTATUS_TSR         (0x1 << 22) /* Trap supervisor return (sret) */

// /* Mask of preserved bits for mstatus */

// #ifdef CONFIG_ARCH_RV32
// #define MSTATUS_WPRI        (0xff << 23 | 0x15)
// #else
// #define MSTATUS_WPRI        (UINT64_C(0x1ffffff) << 38 | UINT64_C(0x1ff) << 23 | 0x15)
// #endif

// /* In mie (machine interrupt enable) register */

// #define MIE_SSIE            (0x1 << 1)  /* Supervisor Software Interrupt Enable */
// #define MIE_MSIE            (0x1 << 3)  /* Machine Software Interrupt Enable */
// #define MIE_STIE            (0x1 << 5)  /* Supervisor Timer Interrupt Enable */
// #define MIE_MTIE            (0x1 << 7)  /* Machine Timer Interrupt Enable */
// #define MIE_SEIE            (0x1 << 9)  /* Supervisor External Interrupt Enable */
// #define MIE_MEIE            (0x1 << 11) /* Machine External Interrupt Enable */

// /* In mip (machine interrupt pending) register */

// #define MIP_SSIP            (0x1 << 1)
// #define MIP_STIP            (0x1 << 5)
// #define MIP_MTIP            (0x1 << 7)
// #define MIP_SEIP            (0x1 << 9)

// /* In sstatus register (which is a view of mstatus) */

// #define SSTATUS_SIE         MSTATUS_SIE
// #define SSTATUS_SPIE        MSTATUS_SPIE
// #define SSTATUS_SPPU        MSTATUS_SPPU
// #define SSTATUS_SPPS        MSTATUS_SPPS
// #define SSTATUS_FS          MSTATUS_FS
// #define SSTATUS_FS_INIT     MSTATUS_FS_INIT
// #define SSTATUS_FS_CLEAN    MSTATUS_FS_CLEAN
// #define SSTATUS_FS_DIRTY    MSTATUS_FS_DIRTY
// #define SSTATUS_SUM         MSTATUS_SUM
// #define SSTATUS_MXR         MSTATUS_MXR

// /* In sie register (which is a view of mie) */

// #define SIE_SSIE            MIE_SSIE
// #define SIE_STIE            MIE_STIE
// #define SIE_SEIE            MIE_SEIE

// /* In sip register (which is a view of mip) */

// #define SIP_SSIP            MIP_SSIP
// #define SIP_STIP            MIP_STIP
// #define SIP_SEIP            MIP_SEIP

// /* In pmpcfg (PMP configuration) register */

// #define PMPCFG_R            (1 << 0)  /* readable ? */
// #define PMPCFG_W            (1 << 1)  /* writable ? */
// #define PMPCFG_X            (1 << 2)  /* executable ? */
// #define PMPCFG_RWX_MASK     (7 << 0)  /* access rights mask */
// #define PMPCFG_A_OFF        (0 << 3)  /* null region (disabled) */
// #define PMPCFG_A_TOR        (1 << 3)  /* top of range */
// #define PMPCFG_A_NA4        (2 << 3)  /* naturally aligned four-byte region */
// #define PMPCFG_A_NAPOT      (3 << 3)  /* naturally aligned power-of-two region */
// #define PMPCFG_A_MASK       (3 << 3)  /* address-matching mode mask */
// #define PMPCFG_L            (1 << 7)  /* locked ? */

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#endif /* __ARCH_LOONGARCH_INCLUDE_CSR_H */

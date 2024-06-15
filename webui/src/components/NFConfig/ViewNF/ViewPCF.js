import {
  NRFSection,
  SBISection,
  LOGSection,
  NF_SBI_Section,  
  MaxSection,
  ParameterSection,
  TimeSection,
  FreeDiameterSection,
  MetricsSection,
  SUPIRangeSection,
  DbUriSection,
  CLISection
} from './ViewCfgSection';

export const ViewPCF= ({ nfconfig }) => {
  const { pcf, parameter, max, time } = nfconfig;

  return (
    <div> 
      <DbUriSection db_uri={nfconfig.db_uri} />
      <LOGSection nfconfig={nfconfig} />
      <NRFSection nfconfig={nfconfig} />
      <SBISection nfconfig={nfconfig} />

      <div>
        {pcf && (
          <div className="nf-section">
            <div className="nf-header">pcf:</div>
            <NF_SBI_Section sbi={pcf.sbi} />
            <FreeDiameterSection freeDiameter={pcf.freeDiameter} />
            <SUPIRangeSection info={pcf.info} />
            <MetricsSection metrics={pcf.metrics} />
          </div>
        )}
      </div>
      {parameter && <ParameterSection parameter={nfconfig.parameter} />}
      {nfconfig && nfconfig.cli && <CLISection cli={nfconfig.cli} />}
      {/*
      <MaxSection max={max} />
      <TimeSection time={time} />
      */}
    </div>
  );
};
